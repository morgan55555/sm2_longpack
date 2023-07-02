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

#ifndef _LONGPACK_PACKER_H_
#define _LONGPACK_PACKER_H_

#include <stdint.h>

#include "LongpackBase.h"

class LongpackPacker {
 public:
  void pack(uint8_t *data, uint16_t len);
  void pack(uint16_t *data, uint16_t len);

  void clean();

  uint16_t available();
  uint8_t read();
  uint8_t peek();

 private:
  uint8_t longpack_[MAX_SYS_CMD_LEN];
  uint16_t longpackLen_ = 0;
  uint8_t *pointer_ = longpack_;
};

#endif //_LONGPACK_PACKER_H_
