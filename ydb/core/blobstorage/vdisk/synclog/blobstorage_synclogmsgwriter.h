#pragma once 
 
#include "defs.h"
#include "blobstorage_synclogformat.h"
#include "blobstorage_synclogmsgimpl.h"
#include <util/generic/buffer.h> 
#include <util/generic/string.h>
#include <util/generic/list.h> 
 
namespace NKikimr { 
    namespace NSyncLog {
 
        ////////////////////////////////////////////////////////////////////////////
        // TNaiveFragmentWriter
        ////////////////////////////////////////////////////////////////////////////
        class TNaiveFragmentWriter {
            TList<TBuffer> Chain;
            size_t DataSize;
 
        public:
            TNaiveFragmentWriter()
                : Chain({{64 << 10}}) // 64 KiB initial storage
                , DataSize(0)
            {}
 
            size_t GetSize() const {
                return DataSize;
            }
 
            void Push(const TRecordHdr *hdr) {
                Push(hdr, hdr->GetSize());
            }

            void Push(const TRecordHdr *hdr, size_t size) {
                Y_VERIFY((size & 3) == 0); // ensure that size is multiple of 4
                const char *d = (const char *)hdr;
                DataSize += size;
                while (size) {
                    TBuffer& buffer = Chain.back();
                    if (!buffer.Avail()) {
                        Chain.emplace_back(512 << 10); // 512 KiB buffer increment
                    } else {
                        size_t len = Min(buffer.Avail(), size);
                        buffer.Append(d, len);
                        d += len;
                        size -= len;
                    }
                } 
            } 

            void Finish(TString *respData);
        };
 
        ////////////////////////////////////////////////////////////////////////////
        // TLz4FragmentWriter
        ////////////////////////////////////////////////////////////////////////////
        class TLz4FragmentWriter : public TNaiveFragmentWriter {
        public:
            TLz4FragmentWriter()
                : TNaiveFragmentWriter()
            {}

            void Finish(TString *respData);
        };

        ////////////////////////////////////////////////////////////////////////////
        // TBaseOrderedWriter -- abstract
        ////////////////////////////////////////////////////////////////////////////
        class TBaseOrderedWriter {
        public:
            TBaseOrderedWriter()
                : DataSize(0)
                , Counter(0)
            {
                // TODO: think about better approximation
                Records.LogoBlobs.reserve(10000); 
            }

            size_t GetSize() const {
                return DataSize;
            }

            void Push(const TRecordHdr *hdr) {
                Push(hdr, hdr->GetSize());
            }

            void Push(const TRecordHdr *hdr, size_t size) {
                Y_VERIFY((size & 3) == 0); // ensure that size is multiple of 4
                switch (hdr->RecType) {
                    case TRecordHdr::RecLogoBlob:
                        Records.LogoBlobs.emplace_back(*hdr->GetLogoBlob(), Counter); 
                        break;
                    case TRecordHdr::RecBlock:
                        Records.Blocks.emplace_back(*hdr->GetBlock(), Counter); 
                        break;
                    case TRecordHdr::RecBarrier:
                        Records.Barriers.emplace_back(*hdr->GetBarrier(), Counter); 
                        break;
                    case TRecordHdr::RecBlockV2: 
                        Records.BlocksV2.emplace_back(*hdr->GetBlockV2(), Counter); 
                        break; 
                    default:
                        Y_FAIL("Unexpected RecType# %" PRIu64, (ui64)hdr->RecType);
                }
                DataSize += size;
                ++Counter;
            }

            // Finish is not implemented, specific codec applies

        protected:
            size_t DataSize;
            ui32 Counter;
            TRecordsWithSerial Records; 
        };

        ////////////////////////////////////////////////////////////////////////////
        // TOrderedLz4FragmentWriter
        ////////////////////////////////////////////////////////////////////////////
        class TOrderedLz4FragmentWriter : public TBaseOrderedWriter {
        public:
            TOrderedLz4FragmentWriter()
                : TBaseOrderedWriter()
            {}

            void Finish(TString *respData);
        };

        ////////////////////////////////////////////////////////////////////////////
        // TCustomCodecFragmentWriter
        ////////////////////////////////////////////////////////////////////////////
        class TCustomCodecFragmentWriter : public TBaseOrderedWriter {
        public:
            TCustomCodecFragmentWriter()
                : TBaseOrderedWriter()
            {}

            void Finish(TString *respData);
        };

    } // NSyncLog
} // NKikimr 
