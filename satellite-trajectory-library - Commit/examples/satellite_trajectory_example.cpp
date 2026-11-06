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

void write_svg(
    const std::string& path,
    const std::vector<sat::orbit::OrbitalState>& trajectory)
{
    constexpr double width = 1000.0;
    constexpr double height = 760.0;
    constexpr double padding = 90.0;
    constexpr double earth_radius = 6378.137;
    const double center_x = width / 2.0;
    const double center_y = height / 2.0;
    const double plot_size = std::min(width - 2.0 * padding, height - 2.0 * padding);

    double extent = earth_radius;
    for (const auto& state : trajectory) {
        extent = std::max(extent, std::abs(state.position[0]));
        extent = std::max(extent, std::abs(state.position[1]));
    }
    extent *= 1.15;
    const double scale = plot_size / (2.0 * extent);
    const auto project_x = [=](double x) { return center_x + x * scale; };
    const auto project_y = [=](double y) { return center_y - y * scale; };

    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error("Could not open SVG output file: " + path);
    }

    output << std::fixed << std::setprecision(2);
    output << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" "
              "height=\"760\" viewBox=\"0 0 1000 760\">\n"
           << "<defs>\n"
              "  <radialGradient id=\"earth\" cx=\"35%\" cy=\"30%\">\n"
              "    <stop offset=\"0%\" stop-color=\"#5ab5ff\"/>\n"
              "    <stop offset=\"100%\" stop-color=\"#123b82\"/>\n"
              "  </radialGradient>\n"
              "  <linearGradient id=\"background\" x2=\"0\" y2=\"1\">\n"
              "    <stop stop-color=\"#071426\"/>\n"
              "    <stop offset=\"100%\" stop-color=\"#101e36\"/>\n"
              "  </linearGradient>\n"
              "</defs>\n"
              "<rect width=\"100%\" height=\"100%\" fill=\"url(#background)\" rx=\"24\"/>\n"
              "<text x=\"90\" y=\"48\" fill=\"#f3f7ff\" font-family=\"Segoe UI, sans-serif\" "
              "font-size=\"26\" font-weight=\"700\">Satellite orbit simulation</text>\n"
           << "<text x=\"90\" y=\"75\" fill=\"#a8bdd8\" font-family=\"Segoe UI, sans-serif\" "
              "font-size=\"15\">RK4 two-body propagation - "
           << trajectory.size() << " samples - "
           << trajectory.back().time / 60.0 << " minutes</text>\n"
           << "<g stroke=\"#22344d\" stroke-width=\"1\">\n"
           << "  <line x1=\"" << center_x << "\" y1=\"" << padding
           << "\" x2=\"" << center_x << "\" y2=\"" << height - padding << "\"/>\n"
           << "  <line x1=\"" << padding << "\" y1=\"" << center_y
           << "\" x2=\"" << width - padding << "\" y2=\"" << center_y << "\"/>\n"
           << "  <circle cx=\"" << center_x << "\" cy=\"" << center_y
           << "\" r=\"" << plot_size / 4.0 << "\" fill=\"none\"/>\n"
           << "  <circle cx=\"" << center_x << "\" cy=\"" << center_y
           << "\" r=\"" << plot_size / 2.0 << "\" fill=\"none\"/>\n"
              "</g>\n"
           << "<circle cx=\"" << center_x << "\" cy=\"" << center_y
           << "\" r=\"" << earth_radius * scale
           << "\" fill=\"url(#earth)\" stroke=\"#82c7ff\" stroke-width=\"2\"/>\n"
              "<path d=\"";

    for (std::size_t i = 0; i < trajectory.size(); ++i) {
        output << (i == 0 ? "M " : " L ")
               << project_x(trajectory[i].position[0]) << ' '
               << project_y(trajectory[i].position[1]);
    }

    const auto& start = trajectory.front();
    const auto& end = trajectory.back();
    output << "\" fill=\"none\" stroke=\"#45e0bd\" stroke-width=\"3\" "
              "stroke-linecap=\"round\" stroke-linejoin=\"round\"/>\n"
           << "<circle cx=\"" << project_x(start.position[0]) << "\" cy=\""
           << project_y(start.position[1])
           << "\" r=\"7\" fill=\"#fff\" stroke=\"#45e0bd\" stroke-width=\"3\"/>\n"
           << "<circle cx=\"" << project_x(end.position[0]) << "\" cy=\""
           << project_y(end.position[1])
           << "\" r=\"7\" fill=\"#ffb454\" stroke=\"#fff\" stroke-width=\"2\"/>\n"
              "<text x=\"90\" y=\"722\" fill=\"#b9c9dd\" "
              "font-family=\"Segoe UI, sans-serif\" font-size=\"14\">Earth radius: "
           << earth_radius
           << " km - X/Y projection (km)</text>\n"
              "<g font-family=\"Segoe UI, sans-serif\" font-size=\"14\">\n"
              "  <circle cx=\"740\" cy=\"46\" r=\"6\" fill=\"#fff\"/>"
              "<text x=\"755\" y=\"51\" fill=\"#dbe7f6\">Start</text>\n"
              "  <circle cx=\"825\" cy=\"46\" r=\"6\" fill=\"#ffb454\"/>"
              "<text x=\"840\" y=\"51\" fill=\"#dbe7f6\">End</text>\n"
              "  <line x1=\"888\" y1=\"46\" x2=\"912\" y2=\"46\" "
              "stroke=\"#45e0bd\" stroke-width=\"3\"/>"
              "<text x=\"920\" y=\"51\" fill=\"#dbe7f6\">Orbit</text>\n"
              "</g>\n"
              "</svg>\n";
    if (!output) {
        throw std::runtime_error("Failed while writing SVG output file: " + path);
    }
}

} // namespace

int main(int argc, char* argv[])
{
    try {
        std::string csv_path;
        std::string svg_path;
        for (int i = 1; i < argc; ++i) {
            const std::string option = argv[i];
            if ((option == "--csv" || option == "--svg") && i + 1 < argc) {
                if (option == "--csv") {
                    csv_path = argv[++i];
                } else {
                    svg_path = argv[++i];
                }
            } else {
                std::cerr << "Usage: satellite_trajectory_example "
                             "[--csv output.csv] [--svg output.svg]\n";
                return 2;
            }
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
        if (!svg_path.empty()) {
            write_svg(svg_path, trajectory);
            std::cout << "SVG orbit plot written to: " << svg_path << '\n';
        }
        std::cout << "\nSimulation completed successfully.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Trajectory demo failed: " << error.what() << '\n';
        return 1;
    }
}
