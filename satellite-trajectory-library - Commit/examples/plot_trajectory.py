#!/usr/bin/env python3
"""Run the C++ orbit demo and render its CSV trajectory as a standalone SVG."""

import argparse
import csv
import subprocess
import sys
from pathlib import Path


WIDTH = 1000
HEIGHT = 760
PADDING = 90
EARTH_RADIUS_KM = 6378.137


def load_trajectory(csv_path):
    with csv_path.open(newline="", encoding="utf-8") as source:
        rows = list(csv.DictReader(source))
    if len(rows) < 2:
        raise ValueError(f"Expected at least two trajectory samples in {csv_path}")
    return [
        (
            float(row["time_s"]) / 60.0,
            float(row["x_km"]),
            float(row["y_km"]),
        )
        for row in rows
    ]


def render_svg(samples, output_path):
    min_x = min(sample[1] for sample in samples)
    max_x = max(sample[1] for sample in samples)
    min_y = min(sample[2] for sample in samples)
    max_y = max(sample[2] for sample in samples)
    half_extent = max(
        abs(min_x), abs(max_x), abs(min_y), abs(max_y), EARTH_RADIUS_KM
    ) * 1.15

    plot_size = min(WIDTH - 2 * PADDING, HEIGHT - 2 * PADDING)
    center_x = WIDTH / 2
    center_y = HEIGHT / 2
    scale = plot_size / (2 * half_extent)

    def project(x, y):
        return center_x + x * scale, center_y - y * scale

    points = [project(x, y) for _, x, y in samples]
    path_data = " ".join(
        ("M" if index == 0 else "L") + f" {x:.2f} {y:.2f}"
        for index, (x, y) in enumerate(points)
    )
    earth_radius = EARTH_RADIUS_KM * scale
    start_x, start_y = points[0]
    end_x, end_y = points[-1]
    duration = samples[-1][0]

    svg = f"""<svg xmlns="http://www.w3.org/2000/svg" width="{WIDTH}" height="{HEIGHT}" viewBox="0 0 {WIDTH} {HEIGHT}">
<defs>
  <radialGradient id="earth" cx="35%" cy="30%">
    <stop offset="0%" stop-color="#5ab5ff"/>
    <stop offset="100%" stop-color="#123b82"/>
  </radialGradient>
  <linearGradient id="background" x2="0" y2="1">
    <stop stop-color="#071426"/>
    <stop offset="100%" stop-color="#101e36"/>
  </linearGradient>
</defs>
<rect width="100%" height="100%" fill="url(#background)" rx="24"/>
<text x="{PADDING}" y="48" fill="#f3f7ff" font-family="Segoe UI, sans-serif" font-size="26" font-weight="700">Satellite orbit simulation</text>
<text x="{PADDING}" y="75" fill="#a8bdd8" font-family="Segoe UI, sans-serif" font-size="15">RK4 two-body propagation · {len(samples)} samples · {duration:.1f} minutes</text>
<g stroke="#22344d" stroke-width="1">
  <line x1="{center_x:.1f}" y1="{PADDING}" x2="{center_x:.1f}" y2="{HEIGHT-PADDING}"/>
  <line x1="{PADDING}" y1="{center_y:.1f}" x2="{WIDTH-PADDING}" y2="{center_y:.1f}"/>
  <circle cx="{center_x:.1f}" cy="{center_y:.1f}" r="{plot_size/4:.1f}" fill="none"/>
  <circle cx="{center_x:.1f}" cy="{center_y:.1f}" r="{plot_size/2:.1f}" fill="none"/>
</g>
<circle cx="{center_x:.1f}" cy="{center_y:.1f}" r="{earth_radius:.2f}" fill="url(#earth)" stroke="#82c7ff" stroke-width="2"/>
<path d="{path_data}" fill="none" stroke="#45e0bd" stroke-width="3" stroke-linecap="round" stroke-linejoin="round"/>
<circle cx="{start_x:.2f}" cy="{start_y:.2f}" r="7" fill="#fff" stroke="#45e0bd" stroke-width="3"/>
<circle cx="{end_x:.2f}" cy="{end_y:.2f}" r="7" fill="#ffb454" stroke="#fff" stroke-width="2"/>
<text x="{PADDING}" y="{HEIGHT-38}" fill="#b9c9dd" font-family="Segoe UI, sans-serif" font-size="14">Earth radius: {EARTH_RADIUS_KM:.1f} km · X/Y projection (km)</text>
<g font-family="Segoe UI, sans-serif" font-size="14">
  <circle cx="{WIDTH-260}" cy="46" r="6" fill="#fff"/><text x="{WIDTH-245}" y="51" fill="#dbe7f6">Start</text>
  <circle cx="{WIDTH-175}" cy="46" r="6" fill="#ffb454"/><text x="{WIDTH-160}" y="51" fill="#dbe7f6">End</text>
  <line x1="{WIDTH-112}" y1="46" x2="{WIDTH-88}" y2="46" stroke="#45e0bd" stroke-width="3"/><text x="{WIDTH-80}" y="51" fill="#dbe7f6">Orbit</text>
</g>
</svg>
"""
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(svg, encoding="utf-8")


def main():
    repo_root = Path(__file__).resolve().parents[1]
    default_executable = repo_root / "build" / "satellite_trajectory_example.exe"
    parser = argparse.ArgumentParser(
        description="Run the C++ satellite orbit demo and create a standalone SVG plot."
    )
    parser.add_argument(
        "--executable",
        type=Path,
        default=default_executable,
        help=f"path to the compiled demo (default: {default_executable})",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=repo_root / "data" / "orbit_trajectory.svg",
        help="SVG output path (default: data/orbit_trajectory.svg)",
    )
    args = parser.parse_args()

    executable = args.executable.resolve()
    if not executable.is_file():
        parser.error(
            f"demo executable not found: {executable}. Build it with "
            "'cmake -S . -B build && cmake --build build'."
        )

    csv_path = args.output.resolve().with_suffix(".csv")
    csv_path.parent.mkdir(parents=True, exist_ok=True)
    try:
        subprocess.run(
            [str(executable), "--csv", str(csv_path)],
            check=True,
        )
        samples = load_trajectory(csv_path)
        render_svg(samples, args.output.resolve())
    except (OSError, subprocess.CalledProcessError, KeyError, ValueError) as error:
        print(f"Could not create trajectory plot: {error}", file=sys.stderr)
        return 1

    print(f"\nTrajectory plot saved to: {args.output.resolve()}")
    print(f"Trajectory CSV saved to: {csv_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
