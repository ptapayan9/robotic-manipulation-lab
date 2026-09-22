#include <iostream>
#include <cmath>

double calculate_position_rad(double target_rad, double curr_rad) {
    return target_rad - curr_rad;
}

int main() {

    double current_angle_rad = 0.2; // where the joint is at now 
    const double target_angle_rad = 0.5; // where we want the joint to be

    const double min_angle_rad = -1.0;
    const double max_angle_rad = 1.0;

    const double correction_fraction = 0.5;

    if (target_angle_rad < min_angle_rad || target_angle_rad > max_angle_rad ){
        std::cerr << "Target angle is outside the permitted range. \n";
        return -1;
    }

    const double tolerance_rad = 0.01;
    const int max_steps = 20;

    for (int step = 0; step < max_steps; ++step){

        const double position_error_rad = calculate_position_rad(target_angle_rad, current_angle_rad);

        if (std::abs(position_error_rad) <= tolerance_rad){
            break;
        }

        current_angle_rad = current_angle_rad + correction_fraction * position_error_rad;

        std::cout << "Step" << step + 1 << ": angle= " << current_angle_rad << " rad\n";
    }

    const double final_error_rad = calculate_position_rad(target_angle_rad, current_angle_rad);
 
    if (std::abs(final_error_rad) <= tolerance_rad){
        std::cout << "Target reached within tolerance. \n";
    } else {
        std::cout << "Target not reached yet. \n";
    }

    std::cout << "Current angle: " << current_angle_rad << " rad\n";
    std::cout << "Target Angle " << target_angle_rad << " rad\n";
    std::cout << "Position Error " << final_error_rad << " rad\n";

    return 0; 
}
