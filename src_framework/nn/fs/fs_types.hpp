#pragma once

#include <nn/nn_common.hpp>

namespace nn::fs {

    /* Handle representing an opened file. */
    struct FileHandle {
        u64 _internal;
    };

    /* Handle representing an opened directory. */
    struct DirectoryHandle {
        u64 _internal;
    };

    /* Kinds of entries within a directory. */
    enum DirectoryEntryType {
        DirectoryEntryType_Directory,
        DirectoryEntryType_File,
    };

    /* Bitfield to define the kinds of entries to open from a directory. */
    enum OpenDirectoryMode : u8 {
        OpenDirectoryMode_Directory = 1 << 0,
        OpenDirectoryMode_File = 1 << 1,

        OpenDirectoryMode_All = OpenDirectoryMode_Directory | OpenDirectoryMode_File,
    };

    /* Maximum length a directory name can be. */
    constexpr inline size_t MaxDirectoryEntryNameSize = 0x300;

    /* Information about an entry within a directory. */
    struct DirectoryEntry {
        char m_Name[MaxDirectoryEntryNameSize + 1];
        OpenDirectoryMode m_Type;
        u32 field_304;
        long m_FileSize;
    };

    /* Mode for opening files. */
    enum OpenMode {
        OpenMode_Read = 1 << 0,
        OpenMode_Write = 1 << 1,
        OpenMode_Append = 1 << 2,

        OpenMode_ReadWrite = OpenMode_Read | OpenMode_Write,
    };

    /* Options for reading. TODO: is this an enum? what for? */
    struct ReadOption {
        int _field_0;

        static inline ReadOption MakeOption(int value) { return {value}; }
    };

    enum WriteOptionFlag {
        WriteOptionFlag_Flush = 1 << 0,
    };

    /* Options for writing. TODO: What else can this do? */
    struct WriteOption {
        int flags;
        static WriteOption CreateOption(int v) {
            return {
                .flags = v,
            };
        }
    };
}; // namespace nn::fs