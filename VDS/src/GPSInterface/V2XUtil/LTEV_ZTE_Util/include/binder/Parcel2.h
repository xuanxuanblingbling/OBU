/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Not a Contribution.
 */

/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PARCEL_H
#define PARCEL_H

#include <string>
typedef int status_t;
typedef std::string String8;
typedef std::u16string String16;

#ifdef __LP64__
# define ULONG_MAX    0xffffffffffffffffUL
#else
# define ULONG_MAX    0xffffffffUL
#endif

#define SIZE_T_MAX ULONG_MAX

// ---------------------------------------------------------------------------
class Parcel {
public:
                        Parcel();
                        ~Parcel();

    const uint8_t*      data() const;
    size_t              dataSize() const;
    size_t              dataAvail() const;
    size_t              dataPosition() const;
    size_t              dataCapacity() const;

    status_t            setDataSize(size_t size);
    void                setDataPosition(size_t pos) const;
    status_t            setDataCapacity(size_t size);

    status_t            setData(const uint8_t* buffer, size_t len);

    status_t            appendFrom(const Parcel *parcel,
                                   size_t start, size_t len);

    status_t            write(const void* data, size_t len);
    status_t            writeInt32(int32_t val);
    status_t            writeInt64(int64_t val);
    status_t            writeString16(const String16& str);
    status_t            writeString16(const char16_t* str, size_t len);

    status_t            read(void* outData, size_t len) const;
    const void*         readInplace(size_t len) const;
    int32_t             readInt32() const;
    status_t            readInt32(int32_t *pArg) const;

    const char16_t*     readString16Inplace(size_t* outLen) const;
    String16            readString16() const;
    void*               writeInplace(size_t len);
    const char*         readCString() const;
    status_t  writeString8AsString16(const char *s);
    uint64_t            readUint64() const;
    status_t            readUint64(uint64_t *pArg) const;
    status_t            writeUint64(uint64_t val);

private:
    status_t            continueWrite(size_t desired);
    status_t            restartWrite(size_t desired);
    void                initState();
    void                freeDataNoInit();
    status_t            growData(size_t len);
    status_t            finishWrite(size_t len);
    template<class T>
    status_t            writeAligned(T val);
    template<class T>
    status_t            readAligned(T *pArg) const;

    template<class T>   T readAligned() const;

    status_t            mError;
    uint8_t*            mData;
    size_t              mDataSize;
    size_t              mDataCapacity;
    mutable size_t      mDataPos;
};

#endif // PARCEL_H
