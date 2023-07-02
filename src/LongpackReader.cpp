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

#include "LongpackReader.h"

ERR_E LongpackReader::read(uint8_t value) {
  if (recv_index_ == 0 && value == MAGIC_PART_1) {
    // parse started
    packData_[recv_index_++] = value;
  } else if (recv_index_ == 1 && value != MAGIC_PART_2) {
    // wrong data, skip
    recv_index_ = 0;
  } else if (recv_index_ > 0) {
    packData_[recv_index_++] = value;
    if (recv_index_ == 6) {
      // len_high(bit 2) concat len_low(bit 3)  = len_check(bit 5)
      if ((packData_[2] ^ packData_[3]) != packData_[5]) {
        // wrong data, skip
        recv_index_ = 0;
      }
    } else if (recv_index_ > 6) {
      if (!dataFieldLen_)
        dataFieldLen_ = packData_[2] << 8 | packData_[3];
      if (dataFieldLen_ + sizeof(PackHead) == recv_index_) {
        packData_[recv_index_] = 0;
        recv_index_ = 0;
        // reach the end of the pack
        uint8_t * dataFiled = packData_ + sizeof(PackHead); // skip the packhead
        uint16_t checksum = CalcChecksum(dataFiled, dataFieldLen_);

        // len_check_high(bit 6) concat len_check_low(bit 7) were calculated by caller.
        // This check will avoid most data corruption.
        if (checksum == ((packData_[6] << 8) | packData_[7])) {
          return E_TRUE;
        } else {
          return E_FALSE;
        }
      }
    }
    // if all above three criteria are not matched, then that is wrong data, skip.
  }

  return E_DOING;
}

ERR_E LongpackReader::read(uint8_t *chunk, uint8_t size) {
  ERR_E result = E_DOING;
  for (uint8_t i = 0; i < size; i++)
  {
    result = read(chunk[i]);
    if (result != E_DOING)
      break;
  }
  return result;
}

void LongpackReader::clean() {
  memset(packData_, 0, sizeof(packData_));
}
