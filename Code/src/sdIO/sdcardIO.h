#include "FS.h"
#include <vector>

//@brief Class for all SDCard I/O function
class sdcardIO
{
    public:

    enum DirectoryEntryType
    {
        Directory,
        File,
        UNKNOWN
    };
    static uint8_t  MountCard();
    static uint64_t GetCardSize();
    static uint64_t GetTotalBytes();
    static uint64_t GetUsedBytes();
    static uint64_t GetFreeBytes();
    
    //@brief Class for Directory specific Methods
    class Directory
    {
        public:
        static std::vector<std::tuple<uint8_t, uint8_t, std::string, size_t>> List(fs::FS &, const char *, uint8_t, uint8_t = 0);
        static bool Create(fs::FS &, const char *);
        static bool Remove(fs::FS &, const char *);
    };
    
    //@brief Class for File specific Methods
    class File
    {
        public:
        static void Read(fs::FS &, const char *);
        static uint8_t Write(fs::FS &, const char *, const char *);
        static uint8_t Append(fs::FS &, const char *, const char *);
        static bool Rename(fs::FS &, const char *, const char *);
        static bool Delete(fs::FS &, const char *);
    };

    static uint8_t ReadConstants(fs::FS &);
};