/*
 * Snapmaker2-Longpack library
 *
 * Based on Snapmaker2-Modules
 * (see https://github.com/Snapmaker/Snapmaker2-Modules)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LongpackBase.h""

uint16_t CalcChecksum(uint8_t *data, uint16_t len) {
  uint32_t checksum = 0;
  for (int i = 0; i < len -1; i = i + 2) {
    checksum += ((data[i] << 8) | data[i + 1]);
  }

  if (len % 2) {
    checksum += data[len - 1];
  }

  while (checksum > 0xffff) {
    checksum = ((checksum >> 16) & 0xffff) + (checksum & 0xffff);
  }
  checksum = ~checksum;

  return checksum;
}