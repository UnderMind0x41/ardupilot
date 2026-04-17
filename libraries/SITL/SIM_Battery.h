/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  battery model for electric aircraft
*/

#pragma once

#include <Filter/LowPassFilter.h>

namespace SITL {

/*
  class to describe a motor position
 */
class Battery {
public:
    void setup(float _capacity_Ah, float _resistance, float _max_voltage);
    void set_capacity(float _capacity_Ah);

    void init_voltage(float voltage);

    void set_current(float current_amps, bool discharge_enabled=true);
    float get_voltage(void) const;
    float get_remaining_Ah(void) const { return remaining_Ah; }

    // return battery temperature in Kelvin:
    float get_temperature(void) const { return temperature.kelvin; }

private:
    float capacity_Ah = 0.0f;
    float resistance = 0.0f;
    float max_voltage = 0.0f;
    float voltage_set = 0.0f;
    float remaining_Ah = 0.0f;
    uint64_t last_us = 0;

    struct {
        float kelvin = 273;
        uint64_t last_update_micros = 0;
    } temperature;

    // 10Hz filter for battery voltage
    LowPassFilterFloat voltage_filter{10};

    float get_resting_voltage(float charge_pct) const;
    void set_initial_SoC(float voltage);
};
}
