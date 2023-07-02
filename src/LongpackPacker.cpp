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

#include "LongpackPacker.h"

void LongpackPacker::pack(uint8_t *data, uint16_t len) {
  if (longpackLen_)
    return;

  uint16_t dataLen = 0;
  dataLen = (data == NULL) ? 0 : len;

  PackHead headInfo;

  headInfo.magic1 = MAGIC_PART_1;
  headInfo.magic2 = MAGIC_PART_2;

  headInfo.lenHigh = dataLen >> 8 & 0xff;
  headInfo.lenLow = dataLen & 0xff;

  headInfo.version = 0x00;

  headInfo.lenCheck = headInfo.lenHigh ^ headInfo.lenLow;

  uint16_t checksum = CalcChecksum(data, len);
  headInfo.dataCheckHigh = checksum >> 8 & 0xff;
  headInfo.dataCheckLow = checksum & 0xff;

  // send head info
  uint8_t * iter = (uint8_t *) &headInfo;
  for (int i = 0; i < 8; ++i) {
    longpack_[longpackLen_++] = (*iter);
    ++iter;
  }

  // send data field
  for (int i = 0; i < len; ++i) {
    longpack_[longpackLen_++] = data[i];
  }

}
void LongpackPacker::pack(uint16_t *data, uint16_t len) {
  pack((uint8_t*) data, len * 2);
}

void LongpackPacker::clean() {
  memset(longpack_, 0, sizeof(longpack_));
  longpackLen_ = 0;
  pointer_ = longpack_;
}

uint16_t LongpackPacker::available() {
  return longpackLen_;
}

uint8_t LongpackPacker::read() {
  if (!longpackLen_)
    return 0;
  
  --longpackLen_;
  return *pointer_++;
}

uint8_t LongpackPacker::peek() {
  if (!longpackLen_)
    return 0;
  
  return *pointer_;
}
