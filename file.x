const MAXLEN = 1024;
typedef string filename<MAXLEN>;
struct request {
    filename name;
    int start;
};
typedef struct request request;
typedef string filechunk<MAXLEN>;
struct chunkreceive {
    filechunk data;
    int bytes;
};
typedef struct chunkreceive chunkreceive;
struct chunksend {
    filename name;
    filechunk data;
    int bytes;
};
typedef struct chunksend chunksend;
union readfile_res switch (int errno) {
    case 0:
        chunkreceive chunk;
    default:
        void;
};
program FTPPROG {
    version FTPVER {
        readfile_res retrieve_file(request *) = 1;
        int send_file(chunksend *) = 2;
    } = 1;
} = 0x20000011;
