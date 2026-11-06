#include "satellite_trajectory/satellite_trajectory.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr double gravitational_parameter = 398600.4418;
constexpr double orbital_radius = 7000.0;

void print_console_plot(const std::vector<sat::orbit::OrbitalState>& trajectory)
{
    constexpr int width = 61;
    constexpr int height = 25;
    constexpr double plot_extent = 8000.0;
    std::vector<std::string> canvas(height, std::string(width, ' '));

    for (const auto& state : trajectory) {
        const auto column = static_cast<int>(
            (state.position[0] + plot_extent) / (2.0 * plot_extent) * (width - 1));
        const auto row = static_cast<int>(
            (plot_extent - state.position[1]) / (2.0 * plot_extent) * (height - 1));
        if (column >= 0 && column < width && row >= 0 && row < height) {
            canvas[row][column] = '*';
        }
    }

    const int center_x = (width - 1) / 2;
    const int center_y = (height - 1) / 2;
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            const double dx = (column - center_x) * (2.0 * plot_extent) / (width - 1);
            const double dy = (row - center_y) * (2.0 * plot_extent) / (height - 1);
            const double distance = std::sqrt(dx * dx + dy * dy);
            if (distance <= 6378.137) {
                canvas[row][column] = 'O';
            } else if (std::abs(distance - 6378.137) < 600.0 &&
                       canvas[row][column] == ' ') {
                canvas[row][column] = '.';
            }
        }
    }

    std::cout << "\nOrbit view (top-down; * satellite path, O Earth):\n";
    for (const auto& line : canvas) {
        std::cout << "  " << line << '\n';
    }
    std::cout << "  " << std::string(width, '-') << "\n"
              << "  -8000 km" << std::string(width - 19, ' ') << "+8000 km (x)\n";
}

void write_csv(
    const std::string& path,
    const std::vector<sat::orbit::OrbitalState>& trajectory)
{
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error("Could not open CSV output file: " + path);
    }

    output << "time_s,x_km,y_km,z_km\n" << std::setprecision(12);
    for (const auto& state : trajectory) {
        output << state.time << ','
               << state.position[0] << ','
               << state.position[1] << ','
               << state.position[2] << '\n';
    }
    if (!output) {
        throw std::runtime_error("Failed while writing CSV output file: " + path);
    }
}

} // namespace

int main(int argc, char* argv[])
{
    try {
        std::string csv_path;
        if (argc == 3 && std::string(argv[1]) == "--csv") {
            csv_path = argv[2];
        } else if (argc != 1) {
            std::cerr << "Usage: satellite_trajectory_example [--csv output.csv]\n";
            return 2;
        }

        const double circular_speed =
            std::sqrt(gravitational_parameter / orbital_radius);
        const sat::orbit::OrbitalState initial{
            sat::num::Vector{orbital_radius, 0.0, 0.0},
            sat::num::Vector{0.0, circular_speed, 0.0},
            0.0
        };

        const double period =
            sat::orbit::orbital_period(orbital_radius, gravitational_parameter);
        sat::orbit::PropagationOptions options;
        options.gravitational_parameter = gravitational_parameter;
        options.time_step = 60.0;
        options.steps = static_cast<std::size_t>(std::ceil(period / options.time_step));
        options.enable_drag = false;

        const auto trajectory = sat::orbit::propagate_rk4(initial, options);
        const auto& final_state = trajectory.back();
        const double final_radius = std::sqrt(
            final_state.position[0] * final_state.position[0] +
            final_state.position[1] * final_state.position[1] +
            final_state.position[2] * final_state.position[2]);

        std::cout << std::fixed << std::setprecision(2)
                  << "============================================================\n"
                  << "         SATELLITE TRAJECTORY - ORBIT DEMO\n"
                  << "============================================================\n"
                  << "Model: circular low Earth orbit, propagated with RK4\n"
                  << "Initial altitude: " << orbital_radius - 6378.137 << " km\n"
                  << "Orbital period:   " << period / 60.0 << " minutes\n"
                  << "Samples:          " << trajectory.size() << "\n";

        print_console_plot(trajectory);

        std::cout << "\nSelected trajectory samples:\n"
                  << "  Time (min)      X (km)      Y (km)      Altitude (km)\n";
        const std::size_t sample_stride = std::max<std::size_t>(1, options.steps / 8);
        for (std::size_t i = 0; i < trajectory.size(); i += sample_stride) {
            const auto& state = trajectory[i];
            const double radius = std::sqrt(
                state.position[0] * state.position[0] +
                state.position[1] * state.position[1] +
                state.position[2] * state.position[2]);
            std::cout << std::setw(11) << state.time / 60.0
                      << std::setw(12) << state.position[0]
                      << std::setw(12) << state.position[1]
                      << std::setw(16) << radius - 6378.137 << '\n';
        }
        if ((trajectory.size() - 1) % sample_stride != 0) {
            std::cout << std::setw(11) << final_state.time / 60.0
                      << std::setw(12) << final_state.position[0]
                      << std::setw(12) << final_state.position[1]
                      << std::setw(16) << final_radius - 6378.137 << '\n';
        }

        if (!csv_path.empty()) {
            write_csv(csv_path, trajectory);
            std::cout << "\nCSV data written to: " << csv_path << '\n';
        }
        std::cout << "\nSimulation completed successfully.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Trajectory demo failed: " << error.what() << '\n';
        return 1;
    }
}
