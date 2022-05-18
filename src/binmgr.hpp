// static __vtbl__20FuncPtrBase__pt__2_v;

class BinFileMgr;
class BinFileBank;

class BinFile {
    public:
        void Init();
        void FetchData();
        void UnFetchData();
        void ScrapData();
        void Load();

        class Header {
            u32 _000;
        };
};

class BinFileGroup {
    public:
        void Init(BinFileBank *);
        void Load();
};

class BinFileBank {
    public:
        void Init(BinFileMgr *);
        void Load();
};

class BinFileMgr {
    public:
        BinFileMgr(char *, char *);
        void Load();
        BinFile* CheckFileNum(u32);
        BinFile* LoadFile(u32);
        void UnLoadFile(u32);
        void* FileData(u32);
        BinFile* File(u32);
        BinFile* NewFile();
        void ScrapAll();
};

class ImageFileMgr {
    public:
        ImageFileMgr(char *);
        BinFile* NewFile();
};

class ImageFile {
    public:
        void Init();
        void Load();
        void FetchData();
        void UnFetchData();
        void ScrapData();
};

void ReadValue(u32 &);
void ReadValue(BinFile::Header&);
void ReadValue(int &);
void ReadValue(long &);

