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

#ifndef _LONGPACK_READER_H_
#define _LONGPACK_READER_H_

#include <stdint.h>

#include "LongpackBase.h"

class LongpackReader {
 public:
  ERR_E read(uint8_t value);
  ERR_E read(uint8_t *chunk, uint8_t size);
  void clean();

  private:
    uint8_t packData_[MAX_SYS_CMD_LEN];
    uint16_t recv_index_ = 0;
    uint16_t dataFieldLen_ = 0;

  public:
    uint8_t *cmd = packData_ + sizeof(PackHead);
};

#endif //_LONGPACK_READER_H_
