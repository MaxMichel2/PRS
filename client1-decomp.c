
int64_t __gmon_start__ = 0;

void _init() {
    int64_t rax1;

    rax1 = __gmon_start__;
    if (rax1) {
        rax1();
    }
    return;
}

int64_t deregister_tm_clones() {
    int64_t rax1;

    *reinterpret_cast<int32_t*>(&rax1) = 0x603130;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax1) + 4) = 0;
    if (1 || (*reinterpret_cast<int32_t*>(&rax1) = 0, *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax1) + 4) = 0, 1)) {
        return rax1;
    } else {
        goto 0;
    }
}

struct s0 {
    int16_t f0;
    int16_t f2;
    int32_t f4;
};

int64_t puts = 0x400c26;

void puts(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto puts;
}

int64_t printf = 0x400c86;

void printf(struct s0* rdi, struct s0* rsi, ...) {
    goto printf;
}

struct s1 {
    signed char[1] pad1;
    int16_t f1;
};

int64_t strlen = 0x400c66;

struct s1* strlen(struct s0* rdi, struct s0* rsi) {
    goto strlen;
}

int64_t sendto = 0x400cb6;

int32_t sendto(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto sendto;
}

int64_t perror = 0x400d86;

void perror(int64_t rdi, struct s0* rsi, struct s0* rdx, ...) {
    goto perror;
}

int64_t exit = 0x400dc6;

void exit(int64_t rdi, struct s0* rsi, struct s0* rdx, ...) {
    goto exit;
}

int64_t atoi = 0x400d96;

int32_t atoi(struct s0* rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto atoi;
}

int64_t memset = 0x400ca6;

void memset(struct s0* rdi, int64_t rsi, int64_t rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto memset;
}

int64_t htons = 0x400c76;

int32_t htons(int64_t rdi, int64_t rsi, int64_t rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto htons;
}

int64_t strcat = 0x400da6;

void strcat(void* rdi, struct s0* rsi) {
    goto strcat;
}

int64_t socket = 0x400e06;

int32_t socket(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8) {
    goto socket;
}

int64_t ntohs = 0x400d56;

uint16_t ntohs(int64_t rdi, struct s0* rsi) {
    goto ntohs;
}

int64_t fopen = 0x400d76;

int64_t fopen(void* rdi, struct s0* rsi) {
    goto fopen;
}

int64_t time = 0x400d16;

int32_t time(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto time;
}

int64_t getpid = 0x400c46;

int32_t getpid(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto getpid;
}

int64_t srand = 0x400cd6;

void srand(struct s0* rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    goto srand;
}

int64_t strncmp = 0x400c16;

int32_t strncmp(void* rdi, void* rsi, int64_t rdx) {
    goto strncmp;
}

int64_t waitpid = 0x400d66;

int32_t waitpid(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto waitpid;
}

int64_t fclose = 0x400c56;

void fclose(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto fclose;
}

int64_t memcpy = 0x400d06;

void memcpy(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto memcpy;
}

int64_t rand = 0x400df6;

int32_t rand(struct s0* rdi, struct s0* rsi, struct s0* rdx, ...) {
    goto rand;
}

int64_t sprintf = 0x400db6;

void sprintf(void* rdi, int64_t rsi, int64_t rdx) {
    goto sprintf;
}

int64_t strncpy = 0x400c06;

void strncpy(struct s0* rdi, void* rsi, int64_t rdx) {
    goto strncpy;
}

int64_t fseek = 0x400d46;

void fseek(int64_t rdi, struct s0* rsi, int64_t rdx, int64_t rcx, struct s0* r8, void* r9) {
    goto fseek;
}

int64_t strcmp = 0x400ce6;

int32_t strcmp(struct s0* rdi, struct s0* rsi) {
    goto strcmp;
}

int32_t fun_400d30(int64_t rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, void* r9);

int64_t my_connect(int32_t edi, struct s0* rsi, struct s0* rdx) {
    void* rbp4;
    struct s1* rax5;
    struct s0* rdx6;
    struct s0* rsi7;
    int64_t rdi8;
    int32_t eax9;
    struct s0* rsi10;
    void* r9_11;
    int64_t rdi12;
    int32_t eax13;
    struct s0* rsi14;
    struct s0* rcx15;
    struct s0* rdx16;
    int32_t eax17;
    int32_t eax18;
    struct s1* rax19;
    struct s0* rdx20;
    struct s0* rsi21;
    int64_t rdi22;
    int32_t eax23;
    int64_t v24;
    int32_t eax25;
    int64_t rdi26;
    int32_t eax27;

    rbp4 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(__zero_stack_offset()) - 8);
    if (*reinterpret_cast<int32_t*>(&rdx)) {
        puts("Sending SYN...", rsi, rdx);
    }
    rax5 = strlen(reinterpret_cast<int64_t>(rbp4) - 44, rsi);
    rdx6 = reinterpret_cast<struct s0*>(&rax5->f1);
    rsi7 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 44);
    *reinterpret_cast<int32_t*>(&rdi8) = edi;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi8) + 4) = 0;
    eax9 = sendto(rdi8, rsi7, rdx6, 0, rsi, 16);
    if (eax9 < 0) {
        perror("ERROR on SYN transmission", rsi7, rdx6, "ERROR on SYN transmission", rsi7, rdx6);
        exit(1, rsi7, rdx6, 1, rsi7, rdx6);
    }
    rsi10 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 80);
    r9_11 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(rbp4) - 48);
    *reinterpret_cast<int32_t*>(&rdi12) = edi;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi12) + 4) = 0;
    eax13 = fun_400d30(rdi12, rsi10, 20, 0, rsi, r9_11);
    if (eax13 < 0) {
        perror("ERROR on SYN-ACK reception. Expected format: SYN-ACK0000", rsi10, 20, "ERROR on SYN-ACK reception. Expected format: SYN-ACK0000", rsi10, 20);
        exit(1, rsi10, 20, 1, rsi10, 20);
    }
    if (*reinterpret_cast<int32_t*>(&rdx)) {
        rsi14 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 80);
        printf("Received message: %s\n", rsi14, "Received message: %s\n", rsi14);
    }
    strncpy(reinterpret_cast<int64_t>(rbp4) - 0x68, reinterpret_cast<int64_t>(rbp4) - 80, 7);
    rcx15 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 0x6d);
    strncpy(rcx15, reinterpret_cast<int64_t>(rbp4) - 80 + 7, 4);
    rdx16 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 40);
    eax17 = strcmp(reinterpret_cast<int64_t>(rbp4) - 0x68, rdx16);
    if (eax17) {
        perror("SYN-ACK expected", rdx16, rdx16);
        exit(1, rdx16, rdx16);
    }
    eax18 = atoi(reinterpret_cast<int64_t>(rbp4) - 0x6d, rdx16, rdx16, rcx15, rsi, r9_11);
    if (*reinterpret_cast<int32_t*>(&rdx)) {
        puts("Sending ACK...", rdx16, rdx16);
    }
    rax19 = strlen(reinterpret_cast<int64_t>(rbp4) - 32, rdx16);
    rdx20 = reinterpret_cast<struct s0*>(&rax19->f1);
    rsi21 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp4) - 32);
    *reinterpret_cast<int32_t*>(&rdi22) = edi;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi22) + 4) = 0;
    eax23 = sendto(rdi22, rsi21, rdx20, 0, rsi, 16);
    if (eax23 < 0) {
        perror("ERROR on ACK transmission", rsi21, rdx20, "ERROR on ACK transmission", rsi21, rdx20);
        exit(1, rsi21, rdx20, 1, rsi21, rdx20);
    }
    memset(reinterpret_cast<int64_t>(rbp4) - 96, 0, 16, 0, rsi, 16);
    *reinterpret_cast<int16_t*>(&v24) = 2;
    eax25 = eax18;
    *reinterpret_cast<uint32_t*>(&rdi26) = *reinterpret_cast<uint16_t*>(&eax25);
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi26) + 4) = 0;
    eax27 = htons(rdi26, 0, 16, 0, rsi, 16);
    *reinterpret_cast<int16_t*>(reinterpret_cast<int64_t>(&v24) + 2) = *reinterpret_cast<int16_t*>(&eax27);
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&v24) + 4) = rsi->f4;
    return v24;
}

int64_t inet_aton = 0x400d26;

void fun_400d20(struct s0* rdi, int32_t* rsi) {
    goto inet_aton;
}

int64_t recvfrom = 0x400d36;

int32_t fun_400d30(int64_t rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, void* r9) {
    goto recvfrom;
}

int64_t gettimeofday = 0x400c96;

void gettimeofday(struct s0* rdi, struct s0* rsi) {
    goto gettimeofday;
}

int32_t read_command_line(int32_t edi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, void* r9) {
    int32_t eax7;
    int32_t eax8;
    int32_t eax9;
    int32_t eax10;
    int32_t eax11;
    int64_t rdi12;
    int32_t eax13;
    int32_t edx14;
    int32_t eax15;

    if (edi == 4)
        goto addr_400f4b_2;
    if (edi == 5) {
        eax7 = strcmp(rcx, "0");
        if (!eax7) {
            addr_400f4b_2:
            eax8 = strcmp(rsi, "127.0.0.1");
            if (eax8) {
                eax9 = strcmp(rsi, "localhost");
                if (eax9) {
                    eax10 = atoi(rdx, "localhost", rdx, rcx, r8, r9);
                    if (eax10 <= 0x3e7 || eax10 > 0x270f) {
                        printf("incorrect port number", "localhost");
                    }
                    memset(r8, 0, 16, rcx, r8, r9);
                    r8->f0 = 2;
                    eax11 = eax10;
                    *reinterpret_cast<uint32_t*>(&rdi12) = *reinterpret_cast<uint16_t*>(&eax11);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi12) + 4) = 0;
                    eax13 = htons(rdi12, 0, 16, rcx, r8, r9);
                    edx14 = eax13;
                    r8->f2 = *reinterpret_cast<int16_t*>(&edx14);
                    fun_400d20(rsi, &r8->f4);
                    eax15 = 0;
                } else {
                    puts("localhost is for babies!", "localhost", rdx);
                    eax15 = -1;
                }
            } else {
                puts("localhost is for babies!", "127.0.0.1", rdx);
                eax15 = -1;
            }
        } else {
            puts("usage: ./client server_ip server_port file_name", "0", rdx);
            eax15 = -1;
        }
    } else {
        puts("usage: ./client server_ip server_port file_name", rsi, rdx);
        eax15 = -1;
    }
    return eax15;
}

int64_t setsockopt = 0x400c36;

void fun_400c30(int64_t rdi, int64_t rsi, int64_t rdx, void* rcx, int64_t r8) {
    goto setsockopt;
}

int64_t fork = 0x400de6;

int32_t fun_400de0(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto fork;
}

int64_t fwrite = 0x400dd6;

int32_t fun_400dd0(void* rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, void* r9) {
    goto fwrite;
}

int64_t ftell = 0x400cf6;

struct s0* fun_400cf0(int64_t rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, void* r9) {
    goto ftell;
}

int64_t close = 0x400cc6;

void fun_400cc0(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto close;
}

void _fini() {
    return;
}

void fun_400ea5() {
    int64_t v1;

    goto v1;
}

void fun_400ecb() {
    return;
}

struct s2 {
    signed char[8] pad8;
    struct s0* f8;
    struct s0* f16;
    struct s0* f24;
    struct s0* f32;
};

struct s3 {
    signed char[2] pad2;
    int16_t f2;
};

int64_t main(int32_t edi, struct s2* rsi) {
    void* rbp3;
    int32_t v4;
    struct s0* rcx5;
    struct s0* rdx6;
    struct s0* rsi7;
    struct s0* r8_8;
    void* r9_9;
    int32_t eax10;
    int32_t v11;
    struct s0* rdi12;
    void* r9_13;
    int32_t eax14;
    struct s0* v15;
    int32_t eax16;
    int32_t v17;
    int64_t rdi18;
    struct s0* rdx19;
    struct s0* rsi20;
    int64_t rax21;
    int64_t v22;
    uint32_t eax23;
    int64_t rdi24;
    uint16_t ax25;
    struct s0* rsi26;
    struct s0* rsi27;
    int64_t rax28;
    int64_t v29;
    int32_t v30;
    int32_t v31;
    struct s0* v32;
    int32_t v33;
    struct s1* rax34;
    struct s0* rdx35;
    struct s0* r8_36;
    int64_t rdi37;
    int32_t eax38;
    int32_t eax39;
    int32_t eax40;
    struct s0* rdi41;
    struct s0* v42;
    struct s3* v43;
    struct s0* v44;
    struct s0* v45;
    int32_t eax46;
    void* v47;
    struct s0* rsi48;
    void* r9_49;
    struct s0* r8_50;
    int64_t rdi51;
    int32_t eax52;
    int32_t eax53;
    struct s0* rsi54;
    int32_t eax55;
    uint32_t eax56;
    unsigned char v57;
    uint32_t eax58;
    unsigned char v59;
    struct s0* rsi60;
    struct s0* rdx61;
    struct s0* rcx62;
    struct s0* rdi63;
    int32_t eax64;
    int32_t v65;
    int32_t eax66;
    struct s0* rsi67;
    struct s0* rsi68;
    struct s0* rdi69;
    struct s0* v70;
    struct s0* v71;
    struct s0* v72;
    struct s0* rdx73;
    int32_t eax74;
    struct s0* v75;
    struct s0* v76;
    struct s0* v77;
    struct s0* v78;
    struct s0* v79;
    struct s0* v80;
    unsigned char al81;
    struct s0* v82;
    struct s0* rdx83;
    int32_t eax84;
    struct s0* v85;
    struct s0* v86;
    struct s0* v87;
    struct s0* v88;
    unsigned char al89;
    struct s0* v90;
    struct s0* v91;
    struct s0* v92;
    unsigned char al93;
    struct s0* v94;
    int32_t v95;
    int64_t rax96;
    int64_t rax97;
    int32_t ecx98;
    int32_t v99;
    int32_t eax100;
    int32_t eax101;
    int64_t rdx102;
    struct s0* rsi103;
    struct s1* rax104;
    struct s0* rdx105;
    int64_t rdi106;
    int32_t eax107;
    int64_t rax108;
    int32_t ecx109;
    int32_t v110;
    struct s0* rdx111;
    int32_t eax112;
    struct s0* rax113;
    int64_t rax114;
    int32_t ecx115;
    struct s0* v116;
    int64_t rdi117;
    int64_t rax118;

    rbp3 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(__zero_stack_offset()) - 8);
    v4 = 0;
    gettimeofday(reinterpret_cast<int64_t>(rbp3) - 0x25050, 0);
    rcx5 = rsi->f32;
    rdx6 = rsi->f16;
    rsi7 = rsi->f8;
    r8_8 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0xb0);
    eax10 = read_command_line(edi, rsi7, rdx6, rcx5, r8_8, r9_9);
    if (eax10 >= 0) {
        v11 = 1;
        if (edi == 5) {
            rdi12 = rsi->f32;
            eax14 = atoi(rdi12, rsi7, rdx6, rcx5, r8_8, r9_13);
            v11 = eax14;
        }
        v15 = rsi->f24;
        strcat(reinterpret_cast<int64_t>(rbp3) - 0x700, v15);
        eax16 = socket(2, 2, 0, rcx5, r8_8);
        v17 = eax16;
        if (v17 < 0) {
            perror("ERROR opening socket", 2, 0, "ERROR opening socket", 2, 0);
            exit(1, 2, 0, 1, 2, 0);
        }
        *reinterpret_cast<int32_t*>(&rdi18) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi18) + 4) = 0;
        fun_400c30(rdi18, 1, 2, reinterpret_cast<int64_t>(rbp3) - 0x250a4, 4);
        *reinterpret_cast<int32_t*>(&rdx19) = v11;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx19) + 4) = 0;
        rsi20 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0xb0);
        rax21 = my_connect(v17, rsi20, rdx19);
        v22 = rax21;
        if (v11) {
            eax23 = *reinterpret_cast<uint16_t*>(reinterpret_cast<int64_t>(&v22) + 2);
            *reinterpret_cast<uint32_t*>(&rdi24) = *reinterpret_cast<uint16_t*>(&eax23);
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi24) + 4) = 0;
            ax25 = ntohs(rdi24, rsi20);
            *reinterpret_cast<uint32_t*>(&rsi26) = ax25;
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi26) + 4) = 0;
            printf("Data connection new port %d\n", rsi26, "Data connection new port %d\n", rsi26);
        }
        *reinterpret_cast<int32_t*>(&rsi27) = reinterpret_cast<int32_t>("wb");
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi27) + 4) = 0;
        rax28 = fopen(reinterpret_cast<int64_t>(rbp3) - 0x700, "wb");
        v29 = rax28;
        if (!v29) {
            perror("ERROR on opening file", "wb", rdx19);
            exit(1, "wb", rdx19);
        }
        v30 = 0;
        while (v30 <= 99) {
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v30 * 4 - 0x8a0) = 0;
            ++v30;
        }
        v31 = 1;
        v32 = reinterpret_cast<struct s0*>(0);
        v33 = 0;
        if (v11) {
            rsi27 = v15;
            printf("Asking for %s on data socket\n", rsi27, "Asking for %s on data socket\n", rsi27);
        }
        rax34 = strlen(v15, rsi27);
        rdx35 = reinterpret_cast<struct s0*>(&rax34->f1);
        r8_36 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250c0);
        *reinterpret_cast<int32_t*>(&rdi37) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi37) + 4) = 0;
        eax38 = sendto(rdi37, v15, rdx35, 0, r8_36, 16);
        if (eax38 < 0) {
            perror("ERROR writing file name", v15, rdx35, "ERROR writing file name", v15, rdx35);
            exit(1, v15, rdx35, 1, v15, rdx35);
        }
        eax39 = time(0, v15, rdx35, 0, r8_36, 16);
        eax40 = getpid(0, v15, rdx35, 0, r8_36, 16);
        *reinterpret_cast<int32_t*>(&rdi41) = eax40 * eax39;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi41) + 4) = 0;
        srand(rdi41, v15, rdx35, 0, r8_36, 16);
        v42 = reinterpret_cast<struct s0*>(&v43->f2);
        v44 = reinterpret_cast<struct s0*>(&v45->f0);
        if (reinterpret_cast<int64_t>(v44) > 0xf423f) {
            v42 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v42) + 1);
            v44 = v44 - 0x1e848;
        }
        eax46 = rand(rdi41, v15, v45, rdi41, v15, v45);
        v47 = reinterpret_cast<void*>(static_cast<int64_t>(eax46 - ((__intrinsic() >> 13) - (eax46 >> 31)) * 0x186a0 + 0x249f0));
        do {
            rsi48 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x690);
            r9_49 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(rbp3) - 0xb4);
            r8_50 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250c0);
            *reinterpret_cast<int32_t*>(&rdi51) = v17;
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi51) + 4) = 0;
            eax52 = fun_400d30(rdi51, rsi48, 0x5dc, 0, r8_50, r9_49);
            if (eax52 < 0) {
                perror("ERROR receiving file", rsi48, 0x5dc, "ERROR receiving file", rsi48, 0x5dc);
                exit(1, rsi48, 0x5dc, 1, rsi48, 0x5dc);
            }
            if (eax52 <= 5 && (eax53 = strncmp(reinterpret_cast<int64_t>(rbp3) - 0x690, reinterpret_cast<int64_t>(rbp3) - 0x704, 3), !!eax53)) {
                *reinterpret_cast<int32_t*>(&rsi54) = eax52;
                *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi54) + 4) = 0;
                printf("Received %d bytes. I need something bigger.\n", rsi54, "Received %d bytes. I need something bigger.\n", rsi54);
            }
            eax55 = strncmp(reinterpret_cast<int64_t>(rbp3) - 0x690, reinterpret_cast<int64_t>(rbp3) - 0x704, 3);
            if (eax55) {
                memcpy(reinterpret_cast<int64_t>(rbp3) - 0x250c7, reinterpret_cast<int64_t>(rbp3) - 0x690, 6);
                if (v11) {
                    eax56 = v57;
                    *reinterpret_cast<int32_t*>(&r9_49) = *reinterpret_cast<signed char*>(&eax56);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r9_49) + 4) = 0;
                    eax58 = v59;
                    *reinterpret_cast<int32_t*>(&r8_50) = *reinterpret_cast<signed char*>(&eax58);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r8_50) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rsi60) = eax52;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi60) + 4) = 0;
                    printf("Message Received: %d bytes seq %c%c%c%c%c%c\n", rsi60, "Message Received: %d bytes seq %c%c%c%c%c%c\n", rsi60);
                }
                rdx61 = reinterpret_cast<struct s0*>(static_cast<int64_t>(eax52 - 6));
                rcx62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x256b0);
                memcpy(rcx62, reinterpret_cast<int64_t>(rbp3) - 0x690 + 6, rdx61);
                rdi63 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250c7);
                eax64 = atoi(rdi63, reinterpret_cast<int64_t>(rbp3) - 0x690 + 6, rdx61, rcx62, r8_50, r9_49);
                v65 = 0;
                eax66 = rand(rdi63, reinterpret_cast<int64_t>(rbp3) - 0x690 + 6, rdx61);
                if (eax66 - ((__intrinsic() >> 5) - (eax66 >> 31)) * 100 <= 10 && (v65 = 1, !!v11)) {
                    *reinterpret_cast<int32_t*>(&rsi67) = eax64;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi67) + 4) = 0;
                    printf("Message %d dropped by the network\n", rsi67, "Message %d dropped by the network\n", rsi67);
                }
                *reinterpret_cast<int32_t*>(&rsi68) = 0;
                *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                rdi69 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x25060);
                gettimeofday(rdi69, 0);
                v70 = reinterpret_cast<struct s0*>(&v42->f0);
                v71 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v47) + reinterpret_cast<int64_t>(v44));
                if (reinterpret_cast<int64_t>(v71) > 0xf423f) {
                    v70 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v70) + 1);
                    v71 = v71 - 0x1e848;
                }
                if (v72 == v42)
                    goto addr_401889_32;
            } else {
                do {
                    *reinterpret_cast<int32_t*>(&rdx73) = 1;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx73) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rsi68) = 0;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                    eax74 = waitpid(0, 0, 1);
                } while (eax74 != -1);
                fclose(v29, 0, 1);
                v31 = 0;
                if (!v11)
                    continue; else
                    goto addr_4016ac_36;
            }
            if (reinterpret_cast<int64_t>(v75) <= reinterpret_cast<int64_t>(v42))
                goto addr_401919_38;
            if (v76 == v70) {
                rdx73 = v77;
                if (reinterpret_cast<int64_t>(rdx73) < reinterpret_cast<int64_t>(v71))
                    goto addr_4018ec_41;
                goto addr_401919_38;
            }
            rdx73 = v78;
            if (reinterpret_cast<int64_t>(rdx73) >= reinterpret_cast<int64_t>(v70)) {
                addr_401919_38:
                if (v79 != v70) {
                    rdx73 = v80;
                    al81 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) > reinterpret_cast<int64_t>(v70));
                } else {
                    rdx73 = v82;
                    al81 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) > reinterpret_cast<int64_t>(v71));
                }
            } else {
                addr_4018ec_41:
                v65 = 1;
                if (v11) {
                    *reinterpret_cast<int32_t*>(&rsi68) = eax64;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rdi69) = reinterpret_cast<int32_t>("Message %d dropped by the network\n");
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi69) + 4) = 0;
                    printf("Message %d dropped by the network\n", rsi68, "Message %d dropped by the network\n", rsi68);
                    goto addr_401baa_47;
                }
            }
            if (al81) {
                v42 = reinterpret_cast<struct s0*>(&v42->f2);
                rdx83 = v44;
                v44 = reinterpret_cast<struct s0*>(&rdx83->f0);
                if (reinterpret_cast<int64_t>(v44) > 0xf423f) {
                    v42 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v42) + 1);
                    v44 = v44 - 0x1e848;
                }
                eax84 = rand(rdi69, 0, rdx83);
                v47 = reinterpret_cast<void*>(static_cast<int64_t>(eax84 - ((__intrinsic() >> 13) - (eax84 >> 31)) * 0x186a0 + 0x249f0));
                v85 = reinterpret_cast<struct s0*>(&v42->f0);
                v86 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v47) + reinterpret_cast<int64_t>(v44));
                if (reinterpret_cast<int64_t>(v86) > 0xf423f) {
                    v85 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v85) + 1);
                    v86 = v86 - 0x1e848;
                }
                if (v87 != v42) {
                    rdx73 = v88;
                    al89 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) > reinterpret_cast<int64_t>(v42));
                } else {
                    rdx73 = v90;
                    al89 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) > reinterpret_cast<int64_t>(v44));
                }
                if (al89) {
                    if (v91 != v85) {
                        rdx73 = v92;
                        al93 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) < reinterpret_cast<int64_t>(v85));
                    } else {
                        rdx73 = v94;
                        al93 = reinterpret_cast<uint1_t>(reinterpret_cast<int64_t>(rdx73) < reinterpret_cast<int64_t>(v86));
                    }
                    if (al93 && (v65 = 1, !!v11)) {
                        *reinterpret_cast<int32_t*>(&rsi68) = eax64;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                        *reinterpret_cast<int32_t*>(&rdi69) = reinterpret_cast<int32_t>("Message %d dropped by the network\n");
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi69) + 4) = 0;
                        printf("Message %d dropped by the network\n", rsi68, "Message %d dropped by the network\n", rsi68);
                    }
                }
            }
            addr_401baa_47:
            if (eax64 >= v4 + 100 || v65) {
                if (v11 && !v65) {
                    *reinterpret_cast<int32_t*>(&rsi68) = eax64;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                    printf("Message %d dropped by the receiver\n", rsi68, "Message %d dropped by the receiver\n", rsi68);
                    continue;
                }
            } else {
                v95 = v4;
                if (eax64 > v4) {
                    *reinterpret_cast<int32_t*>(&rax96) = eax52;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax96) + 4) = 0;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + (eax64 - ((__intrinsic() >> 5) - (eax64 >> 31)) * 100) * 4 - 0x8a0) = static_cast<int32_t>(rax96 - 6);
                    rsi68 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x256b0);
                    rdi69 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x25040 + (eax64 - ((__intrinsic() >> 5) - (eax64 >> 31)) * 100) * 0x5d6);
                    memcpy(rdi69, rsi68, static_cast<int64_t>(eax52 - 6));
                    *reinterpret_cast<int32_t*>(&rax97) = v4;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax97) + 4) = 0;
                    ecx98 = static_cast<int32_t>(rax97 + 1);
                    *reinterpret_cast<int32_t*>(&rdx73) = (__intrinsic() >> 5) - (ecx98 >> 31);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx73) + 4) = 0;
                    v99 = ecx98 - *reinterpret_cast<int32_t*>(&rdx73) * 100;
                    while (!reinterpret_cast<uint1_t>(reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v99 * 4 - 0x8a0) < 0) | reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v99 * 4 - 0x8a0) == 0))) {
                        ++v95;
                        ++v99;
                        if (v99 != 100)
                            continue;
                        v99 = 0;
                    }
                }
                if (v33 == 0x1f4) {
                    do {
                        *reinterpret_cast<int32_t*>(&rdx73) = 1;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx73) + 4) = 0;
                        *reinterpret_cast<int32_t*>(&rsi68) = 0;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                        *reinterpret_cast<int32_t*>(&rdi69) = 0;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi69) + 4) = 0;
                        eax100 = waitpid(0, 0, 1);
                    } while (eax100 != -1);
                    v33 = 0;
                }
                eax101 = fun_400de0(rdi69, rsi68, rdx73);
                if (eax101 < 0) {
                    perror("ERROR creating process", rsi68, rdx73);
                    exit(1, rsi68, rdx73);
                }
                if (!eax101) {
                    *reinterpret_cast<int32_t*>(&rdx102) = v95;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx102) + 4) = 0;
                    sprintf(reinterpret_cast<int64_t>(rbp3) - 0x250d8, "%06d", rdx102);
                    strncpy(reinterpret_cast<int64_t>(rbp3) - 0x250d1, reinterpret_cast<int64_t>(rbp3) - 0x708, 4);
                    rsi103 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250d8);
                    strcat(reinterpret_cast<int64_t>(rbp3) - 0x250d1, rsi103);
                    rax104 = strlen(reinterpret_cast<int64_t>(rbp3) - 0x250d1, rsi103);
                    rdx105 = reinterpret_cast<struct s0*>(&rax104->f1);
                    rsi68 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250d1);
                    *reinterpret_cast<int32_t*>(&r9_49) = 16;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r9_49) + 4) = 0;
                    r8_50 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250c0);
                    *reinterpret_cast<int32_t*>(&rdi106) = v17;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi106) + 4) = 0;
                    eax107 = sendto(rdi106, rsi68, rdx105, 0, r8_50, 16);
                    if (v11) {
                        rsi68 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x250d1);
                        printf("Sent %s\n", rsi68, "Sent %s\n", rsi68);
                    }
                    if (eax107 < 0) {
                        perror("ERROR sending ACK", rsi68, rdx105, "ERROR sending ACK", rsi68, rdx105);
                        exit(1, rsi68, rdx105, 1, rsi68, rdx105);
                    }
                    exit(0, rsi68, rdx105, 0, rsi68, rdx105);
                }
                ++v33;
                *reinterpret_cast<int32_t*>(&rax108) = v4;
                *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax108) + 4) = 0;
                ecx109 = static_cast<int32_t>(rax108 + 1);
                *reinterpret_cast<int32_t*>(&rdx73) = (__intrinsic() >> 5) - (ecx109 >> 31);
                *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx73) + 4) = 0;
                v110 = ecx109 - *reinterpret_cast<int32_t*>(&rdx73) * 100;
                while (!reinterpret_cast<uint1_t>(reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v110 * 4 - 0x8a0) < 0) | reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v110 * 4 - 0x8a0) == 0))) {
                    rdx111 = reinterpret_cast<struct s0*>(static_cast<int64_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v110 * 4 - 0x8a0)));
                    eax112 = fun_400dd0(reinterpret_cast<int64_t>(rbp3) - 0x25040 + v110 * 0x5d6, 1, rdx111, v29, r8_50, r9_49);
                    v32 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(v32) + eax112);
                    rax113 = fun_400cf0(v29, 1, rdx111, v29, r8_50, r9_49);
                    if (rax113 != v32) {
                        perror("ERROR on file position indicator\n", 1, rdx111, "ERROR on file position indicator\n", 1, rdx111);
                        exit(1, 1, rdx111, 1, 1, rdx111);
                    }
                    *reinterpret_cast<int32_t*>(&rsi68) = 0;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi68) + 4) = 0;
                    fseek(v29, 0, 2, v29, r8_50, r9_49);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v110 * 4 - 0x8a0) = 0;
                    ++v4;
                    *reinterpret_cast<int32_t*>(&rax114) = v4;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax114) + 4) = 0;
                    ecx115 = static_cast<int32_t>(rax114 + 1);
                    *reinterpret_cast<int32_t*>(&rdx73) = (__intrinsic() >> 5) - (ecx115 >> 31);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx73) + 4) = 0;
                    v110 = ecx115 - *reinterpret_cast<int32_t*>(&rdx73) * 100;
                }
                continue;
            }
            addr_401889_32:
            if (reinterpret_cast<int64_t>(v116) <= reinterpret_cast<int64_t>(v44)) {
                goto addr_401919_38;
            }
            addr_4016ac_36:
            puts("Received FIN", 0, 1);
        } while (v31);
        if (v11) {
            rsi68 = v32;
            printf("Total bytes received %ld\n", rsi68, "Total bytes received %ld\n", rsi68);
        }
        *reinterpret_cast<int32_t*>(&rdi117) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi117) + 4) = 0;
        fun_400cc0(rdi117, rsi68, rdx73);
        *reinterpret_cast<int32_t*>(&rax118) = 0;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax118) + 4) = 0;
    } else {
        *reinterpret_cast<int32_t*>(&rax118) = -1;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax118) + 4) = 0;
    }
    return rax118;
}

void __libc_csu_fini() {
    return;
}

void fun_400e6a() {
    if (1)
        goto 0x400ea8;
    if (1)
        goto 0x400ea8;
    goto 0;
}

signed char __TMC_END__ = 0;

int64_t __do_global_dtors_aux() {
    int1_t zf1;
    int64_t rax2;

    zf1 = __TMC_END__ == 0;
    if (!zf1)
        goto 0x400ed0;
    rax2 = deregister_tm_clones();
    __TMC_END__ = 1;
    return rax2;
}

void frame_dummy() {
    goto 0x400e70;
}

int64_t g603010 = 0;

void fun_400c26() {
    goto g603010;
}

void fun_400c86() {
    goto 0x400bf0;
}

void fun_400c66() {
    goto 0x400bf0;
}

void fun_400cb6() {
    goto 0x400bf0;
}

void fun_400d86() {
    goto 0x400bf0;
}

void fun_400dc6() {
    goto 0x400bf0;
}

void fun_400d96() {
    goto 0x400bf0;
}

void fun_400ca6() {
    goto 0x400bf0;
}

void fun_400c76() {
    goto 0x400bf0;
}

void __libc_csu_init(int32_t edi, int64_t rsi, int64_t rdx) {
    int64_t r15_4;
    int32_t r13d5;
    int64_t r14_6;
    int64_t rbx7;
    int64_t rdi8;

    r15_4 = rdx;
    r13d5 = edi;
    r14_6 = rsi;
    _init();
    if (!0) {
        *reinterpret_cast<int32_t*>(&rbx7) = 0;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rbx7) + 4) = 0;
        do {
            *reinterpret_cast<int32_t*>(&rdi8) = r13d5;
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi8) + 4) = 0;
            *reinterpret_cast<int64_t*>(0x602e00 + rbx7 * 8)(rdi8, r14_6, r15_4);
            ++rbx7;
        } while (1 != rbx7);
    }
    return;
}

void fun_400da6() {
    goto 0x400bf0;
}

void fun_400e06() {
    goto 0x400bf0;
}

void fun_400d56() {
    goto 0x400bf0;
}

void fun_400d76() {
    goto 0x400bf0;
}

void fun_400d16() {
    goto 0x400bf0;
}

void fun_400c46() {
    goto 0x400bf0;
}

void fun_400cd6() {
    goto 0x400bf0;
}

void fun_400c16() {
    goto 0x400bf0;
}

void fun_400d66() {
    goto 0x400bf0;
}

void fun_400c56() {
    goto 0x400bf0;
}

void fun_400d06() {
    goto 0x400bf0;
}

void fun_400df6() {
    goto 0x400bf0;
}

void fun_400db6() {
    goto 0x400bf0;
}

void fun_400c06() {
    goto 0x400bf0;
}

void fun_400d46() {
    goto 0x400bf0;
}

void fun_400ce6() {
    goto 0x400bf0;
}

void fun_400d26() {
    goto 0x400bf0;
}

void fun_400d36() {
    goto 0x400bf0;
}

void fun_400c96() {
    goto 0x400bf0;
}

int64_t __libc_start_main = 0;

void _start() {
    void* rsp1;
    int64_t rdx2;
    int64_t rax3;

    rsp1 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(__zero_stack_offset()) + 8);
    __libc_start_main(main, __return_address(), rsp1, __libc_csu_init, __libc_csu_fini, rdx2, (reinterpret_cast<uint64_t>(rsp1) & 0xfffffffffffffff0) - 8 - 8, rax3);
    __asm__("hlt ");
}

void fun_400c36() {
    goto 0x400bf0;
}

void fun_400de6() {
    goto 0x400bf0;
}

void fun_400dd6() {
    goto 0x400bf0;
}

void fun_400cf6() {
    goto 0x400bf0;
}

void fun_400cc6() {
    goto 0x400bf0;
}
