// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Log format information shared by reader and writer.
// See ../doc/log_format.md for more detail.

#ifndef STORAGE_LEVELDB_DB_LOG_FORMAT_H_
#define STORAGE_LEVELDB_DB_LOG_FORMAT_H_

namespace leveldb {
namespace log {

enum RecordType {
  // Zero is reserved for preallocated files
  kZeroType = 0,//预分配的文件

  kFullType = 1,//该条log，都在这个block上

  // For fragments
  kFirstType = 2,//该条log的头部，在这个block上
  kMiddleType = 3,//该条log的中间
  kLastType = 4//该条log的尾部
};
static const int kMaxRecordType = kLastType;

static const int kBlockSize = 32768;//32kB = 32*1024B

// Header is checksum (4 bytes), length (2 bytes), type (1 byte).
static const int kHeaderSize = 4 + 2 + 1;//header是一个int8_t

}  // namespace log
}  // namespace leveldb

#endif  // STORAGE_LEVELDB_DB_LOG_FORMAT_H_
