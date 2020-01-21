argc
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

    *reinterpret_cast<int32_t*>(&rax1) = 0x603138;
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
};

int64_t puts = 0x400c66;

void puts(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto puts;
}

int64_t printf = 0x400cc6;

void printf(struct s0* rdi, struct s0* rsi, ...) {
    goto printf;
}

struct s1 {
    signed char[1] pad1;
    int16_t f1;
};

int64_t strlen = 0x400ca6;

struct s1* strlen(struct s0* rdi, struct s0* rsi) {
    goto strlen;
}

struct s2 {
    int64_t f0;
    int64_t f8;
};

int64_t sendto = 0x400cf6;

int32_t sendto(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, struct s2* r9) {
    goto sendto;
}

int64_t perror = 0x400dc6;

void perror(int64_t rdi, struct s0* rsi, struct s0* rdx, ...) {
    goto perror;
}

int64_t exit = 0x400e06;

void exit(int64_t rdi, struct s0* rsi, struct s0* rdx, ...) {
    goto exit;
}

int64_t atoi = 0x400dd6;

uint32_t atoi(struct s0* rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8, struct s2* r9) {
    goto atoi;
}

int64_t memset = 0x400ce6;

void memset(struct s0* rdi, int64_t rsi, int64_t rdx, struct s0* rcx, struct s0* r8, struct s2* r9) {
    goto memset;
}

int64_t htons = 0x400cb6;

int32_t htons(int64_t rdi, int64_t rsi, int64_t rdx, struct s0* rcx, struct s0* r8, struct s2* r9) {
    goto htons;
}

uint32_t rand(struct s0* rdi, struct s0* rsi, ...);

int32_t drop_message(struct s0* rdi, struct s0* rsi) {
    struct s0* rdi3;
    struct s0* rsi4;
    int32_t edx5;
    int1_t cf6;
    uint32_t eax7;
    struct s0* rdi8;
    struct s0* rsi9;
    struct s0* rdi10;
    struct s0* rsi11;
    struct s0* rdi12;
    struct s0* rsi13;
    struct s0* rdi14;
    struct s0* rsi15;
    struct s0* rdi16;
    struct s0* rsi17;
    struct s0* rdi18;
    struct s0* rsi19;
    struct s0* rdi20;
    struct s0* rsi21;
    uint32_t eax22;
    struct s0* rdi23;
    struct s0* rsi24;

    rdi->f0 = rsi->f0;
    rdi3 = rdi + 1;
    rsi4 = rsi + 1;
    edx5 = (__intrinsic() >> 3) - (*reinterpret_cast<int32_t*>(&rsi4) >> 31);
    cf6 = 0;
    if (!(*reinterpret_cast<int32_t*>(&rsi4) - ((edx5 << 2) + edx5 << 2))) {
        eax7 = rand(rdi3, rsi4);
        cf6 = eax7 < ((__intrinsic() >> 5) - (reinterpret_cast<int32_t>(eax7) >> 31)) * 100;
        __asm__("cvtsi2sd xmm0, eax");
        rdi3->f0 = rsi4->f0;
        rdi8 = rdi3 + 1;
        rsi9 = rsi4 + 1;
        __asm__("divsd xmm0, xmm1");
        rdi8->f0 = rsi9->f0;
        rdi10 = rdi8 + 1;
        rsi11 = rsi9 + 1;
        __asm__("mulsd xmm0, xmm1");
        rdi10->f0 = rsi11->f0;
        rdi3 = rdi10 + 1;
        rsi4 = rsi11 + 1;
    }
    rdi3->f0 = rsi4->f0;
    rdi12 = rdi3 + 1;
    rsi13 = rsi4 + 1;
    rdi12->f0 = rsi13->f0;
    rdi14 = rdi12 + 1;
    rsi15 = rsi13 + 1;
    rdi14->f0 = rsi15->f0;
    rdi16 = rdi14 + 1;
    rsi17 = rsi15 + 1;
    rdi16->f0 = rsi17->f0;
    rdi18 = rdi16 + 1;
    rsi19 = rsi17 + 1;
    __asm__("ucomisd xmm0, xmm1");
    if (!cf6) {
        rdi18->f0 = rsi19->f0;
        rdi20 = rdi18 + 1;
        rsi21 = rsi19 + 1;
        rdi20->f0 = rsi21->f0;
        rdi18 = rdi20 + 1;
        rsi19 = rsi21 + 1;
    }
    eax22 = rand(rdi18, rsi19);
    __asm__("cvtsi2sd xmm0, eax");
    rdi18->f0 = rsi19->f0;
    rdi23 = rdi18 + 1;
    rsi24 = rsi19 + 1;
    __asm__("divsd xmm0, xmm1");
    rdi23->f0 = rsi24->f0;
    (rdi23 + 1)->f0 = (rsi24 + 1)->f0;
    __asm__("ucomisd xmm0, [rbp-0x10]");
    if (eax22 <= ((__intrinsic() >> 5) - (reinterpret_cast<int32_t>(eax22) >> 31)) * 100) {
    }
    return 0;
}

int64_t rand = 0x400e36;

uint32_t rand(struct s0* rdi, struct s0* rsi, ...) {
    goto rand;
}

int32_t strcmp(struct s0* rdi, struct s0* rsi);

void inet_aton(struct s0* rdi, struct s0* rsi);

int32_t read_command_line(int32_t argc, struct s0* argv, struct s0* rdx, struct s0* rcx, struct s0* r8, struct s2* r9) {
    struct s0* v7;
    int32_t eax8;
    uint32_t eax9;
    int32_t eax10;
    uint32_t eax11;
    int64_t rdi12;
    int32_t eax13;
    int32_t edx14;

    v7 = argv;
    if (argc == 4)
        goto addr_400f9b_2;
    if (argc == 5) {
        *reinterpret_cast<int32_t*>(&argv) = reinterpret_cast<int32_t>("0");
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&argv) + 4) = 0;
        eax8 = strcmp(rcx, "0");
        if (!eax8) {
            addr_400f9b_2:
            eax9 = atoi(rdx, argv, rdx, rcx, r8, r9);
            if (reinterpret_cast<int32_t>(eax9) <= reinterpret_cast<int32_t>(0x3e7) || reinterpret_cast<int32_t>(eax9) > reinterpret_cast<int32_t>(0x270f)) {
                printf("incorrect port number", argv);
            }
        } else {
            puts("usage: ./client server_ip server_port file_name", "0", rdx);
            eax10 = -1;
            goto addr_40101d_7;
        }
    } else {
        puts("usage: ./client server_ip server_port file_name", argv, rdx);
        eax10 = -1;
        goto addr_40101d_7;
    }
    memset(r8, 0, 16, rcx, r8, r9);
    r8->f0 = 2;
    eax11 = eax9;
    *reinterpret_cast<uint32_t*>(&rdi12) = *reinterpret_cast<uint16_t*>(&eax11);
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi12) + 4) = 0;
    eax13 = htons(rdi12, 0, 16, rcx, r8, r9);
    edx14 = eax13;
    r8->f2 = *reinterpret_cast<int16_t*>(&edx14);
    inet_aton(v7, r8 + 1);
    eax10 = 0;
    addr_40101d_7:
    return eax10;
}

int64_t strcat = 0x400de6;

void strcat(struct s0* rdi, struct s0* rsi) {
    goto strcat;
}

int64_t socket = 0x400e56;

int32_t socket(int64_t rdi, struct s0* rsi, struct s0* rdx, struct s0* rcx, struct s0* r8) {
    goto socket;
}

int64_t ntohs = 0x400d96;

uint16_t ntohs(int64_t rdi, struct s0* rsi) {
    goto ntohs;
}

int64_t fopen = 0x400db6;

int64_t fopen(void* rdi, struct s0* rsi) {
    goto fopen;
}

int64_t time = 0x400d56;

int32_t time(int64_t rdi) {
    goto time;
}

int64_t getpid = 0x400c86;

int32_t getpid(int64_t rdi) {
    goto getpid;
}

int64_t srand = 0x400d16;

void srand() {
    goto srand;
}

int64_t recvfrom = 0x400d76;

int32_t recvfrom(int64_t rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, struct s2* r9) {
    goto recvfrom;
}

int64_t waitpid = 0x400da6;

int32_t waitpid(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto waitpid;
}

int64_t fclose = 0x400c96;

void fclose(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto fclose;
}

int64_t memcpy = 0x400d46;

void memcpy(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto memcpy;
}

int64_t sprintf = 0x400df6;

void sprintf(void* rdi, int64_t rsi, int64_t rdx) {
    goto sprintf;
}

int64_t strncpy = 0x400c46;

void strncpy(struct s0* rdi, void* rsi, int64_t rdx) {
    goto strncpy;
}

int64_t usleep = 0x400e46;

void usleep(struct s0* rdi, struct s0* rsi) {
    goto usleep;
}

int64_t fseek = 0x400d86;

void fseek(int64_t rdi, struct s0* rsi, int64_t rdx, int64_t rcx, struct s0* r8, struct s2* r9) {
    goto fseek;
}

int64_t strcmp = 0x400d26;

int32_t strcmp(struct s0* rdi, struct s0* rsi) {
    goto strcmp;
}

int64_t my_connect(int32_t edi, struct s0* rsi, struct s0* rdx) {
    void* rbp4;
    struct s1* rax5;
    struct s0* rdx6;
    struct s0* rsi7;
    int64_t rdi8;
    int32_t eax9;
    struct s0* rsi10;
    struct s2* r9_11;
    int64_t rdi12;
    int32_t eax13;
    struct s0* rsi14;
    struct s0* rcx15;
    struct s0* rdx16;
    int32_t eax17;
    uint32_t eax18;
    struct s1* rax19;
    struct s0* rdx20;
    struct s0* rsi21;
    int64_t rdi22;
    int32_t eax23;
    int64_t v24;
    uint32_t eax25;
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
    r9_11 = reinterpret_cast<struct s2*>(reinterpret_cast<int64_t>(rbp4) - 48);
    *reinterpret_cast<int32_t*>(&rdi12) = edi;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi12) + 4) = 0;
    eax13 = recvfrom(rdi12, rsi10, 20, 0, rsi, r9_11);
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
    *reinterpret_cast<int16_t*>(reinterpret_cast<int64_t>(&v24) + 4) = (rsi + 1)->f0;
    return v24;
}

int64_t inet_aton = 0x400d66;

void inet_aton(struct s0* rdi, struct s0* rsi) {
    goto inet_aton;
}

void gettimeofday();

struct s3 {
    int64_t f0;
    int64_t f8;
};

int64_t peek(int32_t edi, int32_t* rsi, int32_t* rdx, void* rcx, struct s0* r8, struct s2* r9, int64_t* a7, int64_t a8) {
    int32_t ecx9;
    int64_t rax10;
    struct s3* rcx11;
    int64_t v12;
    int64_t v13;
    int64_t v14;
    int64_t v15;

    gettimeofday();
    *rsi = *rsi + edi;
    ecx9 = *rdx;
    *reinterpret_cast<int32_t*>(&rax10) = *rdx;
    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax10) + 4) = 0;
    *rdx = static_cast<int32_t>(rax10 + 1);
    rcx11 = reinterpret_cast<struct s3*>((static_cast<int64_t>(ecx9 - (((__intrinsic() >> 3) - (ecx9 >> 31) << 2) + ((__intrinsic() >> 3) - (ecx9 >> 31)) << 2)) << 4) + reinterpret_cast<int64_t>(a7));
    rcx11->f0 = v12;
    rcx11->f8 = v13;
    if (*rdx != 1) {
        if (*rdx > 19) {
            if (ecx9 - (((__intrinsic() >> 3) - (ecx9 >> 31) << 2) + ((__intrinsic() >> 3) - (ecx9 >> 31)) << 2) != 19) {
            }
        }
        __asm__("cvtsi2sd xmm0, eax");
        __asm__("cvtsi2sd xmm1, qword [rbp-0x20]");
        __asm__("divsd xmm0, xmm1");
        __asm__("cvtsi2sd xmm0, dword [rbp-0xc]");
        __asm__("cvtsi2sd xmm1, qword [rbp-0x18]");
        __asm__("divsd xmm0, xmm1");
    } else {
        r9->f0 = v14;
        r9->f8 = v15;
    }
    return 1;
}

int64_t setsockopt = 0x400c76;

void setsockopt(int64_t rdi, int64_t rsi, int64_t rdx, void* rcx, int64_t r8) {
    goto setsockopt;
}

int64_t strncmp = 0x400c56;

int32_t strncmp(void* rdi, void* rsi, int64_t rdx) {
    goto strncmp;
}

int64_t fork = 0x400e26;

int32_t fork(struct s0* rdi, struct s0* rsi, struct s0* rdx) {
    goto fork;
}

int64_t fwrite = 0x400e16;

uint32_t fwrite(void* rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, struct s2* r9) {
    goto fwrite;
}

int64_t ftell = 0x400d36;

uint32_t ftell(int64_t rdi, struct s0* rsi, struct s0* rdx, int64_t rcx, struct s0* r8, struct s2* r9) {
    goto ftell;
}

int64_t close = 0x400d06;

void close(int64_t rdi, struct s0* rsi, struct s0* rdx) {
    goto close;
}

int64_t gettimeofday = 0x400cd6;

void gettimeofday() {
    goto gettimeofday;
}

void _fini() {
    return;
}

void fun_400ef5() {
    int64_t v1;

    goto v1;
}

void fun_400f1b() {
    return;
}

void __libc_csu_fini() {
    return;
}

void fun_400eba() {
    if (1)
        goto 0x400ef8;
    if (1)
        goto 0x400ef8;
    goto 0;
}

signed char __TMC_END__ = 0;

int64_t __do_global_dtors_aux() {
    int1_t zf1;
    int64_t rax2;

    zf1 = __TMC_END__ == 0;
    if (!zf1)
        goto 0x400f20;
    rax2 = deregister_tm_clones();
    __TMC_END__ = 1;
    return rax2;
}

void frame_dummy() {
    goto 0x400ec0;
}

int64_t g603010 = 0;

void fun_400c66() {
    goto g603010;
}

void fun_400cc6() {
    goto 0x400c30;
}

void fun_400ca6() {
    goto 0x400c30;
}

void fun_400cf6() {
    goto 0x400c30;
}

void fun_400dc6() {
    goto 0x400c30;
}

void fun_400e06() {
    goto 0x400c30;
}

void fun_400dd6() {
    goto 0x400c30;
}

void fun_400ce6() {
    goto 0x400c30;
}

void fun_400cb6() {
    goto 0x400c30;
}

void fun_400e36() {
    goto 0x400c30;
}

struct s4 {
    int32_t f0;
    int32_t f4;
};

struct s5 {
    int32_t f0;
    int32_t f4;
    struct s0* f8;
    struct s0* f16;
    struct s0* f24;
    struct s0* f32;
};

int16_t socket;

int64_t main(struct s4* argc, struct s5* argv) {
    void* rbp3;
    uint32_t v4;
    struct s0* rcx5;
    struct s0* rdx6;
    struct s0* rsi7;
    struct s0* r8_8;
    struct s2* r9_9;
    int32_t eax10;
    uint32_t v11;
    struct s0* rdi12;
    struct s2* r9_13;
    uint32_t eax14;
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
    uint32_t v32;
    int32_t v33;
    struct s1* rax34;
    struct s0* rdx35;
    int64_t rdi36;
    int32_t eax37;
    int32_t v38;
    int32_t eax39;
    int32_t eax40;
    struct s0* rdi41;
    struct s0* rdi42;
    struct s0* rsi43;
    struct s0* rsi44;
    int64_t rdi45;
    int64_t v46;
    int32_t eax47;
    struct s2* r9_48;
    struct s0* r8_49;
    int32_t eax50;
    struct s0* rdx51;
    struct s0* rcx52;
    struct s0* rdi53;
    uint32_t eax54;
    uint32_t eax55;
    unsigned char v56;
    uint32_t eax57;
    unsigned char v58;
    struct s0* rsi59;
    struct s0* rdx60;
    struct s0* v61;
    struct s0* rsi62;
    struct s0* rdi63;
    int32_t eax64;
    uint32_t v65;
    int64_t rax66;
    int64_t rax67;
    int32_t ecx68;
    int32_t v69;
    int32_t eax70;
    int32_t eax71;
    int64_t rdx72;
    struct s0* rdi73;
    uint32_t eax74;
    struct s0* rdi75;
    uint32_t eax76;
    struct s0* rdx77;
    struct s1* rax78;
    int64_t rdi79;
    int32_t eax80;
    int64_t rax81;
    int32_t ecx82;
    int32_t v83;
    struct s0* rdx84;
    uint32_t eax85;
    uint32_t eax86;
    int64_t rax87;
    int32_t ecx88;
    int32_t eax89;
    int64_t rdi90;
    int64_t rax91;

    rbp3 = reinterpret_cast<void*>(reinterpret_cast<int64_t>(__zero_stack_offset()) - 8);
    v4 = 0;
    __asm__("pxor xmm0, xmm0");
    argc->f0 = argv->f0;
    __asm__("pxor xmm0, xmm0");
    argc->f4 = argv->f4;
    rcx5 = argv->f32;
    rdx6 = argv->f16;
    rsi7 = argv->f8;
    r8_8 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0xa0);
    eax10 = read_command_line(*reinterpret_cast<int32_t*>(&argc), rsi7, rdx6, rcx5, r8_8, r9_9);
    if (eax10 >= 0) {
        v11 = 1;
        if (*reinterpret_cast<int32_t*>(&rdi) == 5) {
            rdi12 = argv->f32;
            eax14 = atoi(rdi12, rsi7, rdx6, rcx5, r8_8, r9_13);
            v11 = eax14;
        }
        v15 = argv->f24;
        strcat(reinterpret_cast<int64_t>(rbp3) - 0x6f0, v15);
        eax16 = socket(2, 2, 0, rcx5, r8_8);
        v17 = eax16;
        if (v17 < 0) {
            perror("ERROR opening socket", 2, 0, "ERROR opening socket", 2, 0);
            exit(1, 2, 0, 1, 2, 0);
        }
        *reinterpret_cast<int32_t*>(&rdi18) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi18) + 4) = 0;
        setsockopt(rdi18, 1, 2, reinterpret_cast<int64_t>(rbp3) - 0x251a4, 4);
        *reinterpret_cast<uint32_t*>(&rdx19) = v11;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx19) + 4) = 0;
        rsi20 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0xa0);
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
        rax28 = fopen(reinterpret_cast<int64_t>(rbp3) - 0x6f0, "wb");
        v29 = rax28;
        if (!v29) {
            perror("ERROR on opening file", "wb", rdx19);
            exit(1, "wb", rdx19);
        }
        v30 = 0;
        while (v30 <= 99) {
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v30 * 4 - 0x890) = 0;
            ++v30;
        }
        v31 = 1;
        v32 = 0;
        v33 = 0;
        if (v11) {
            rsi27 = v15;
            printf("Asking for %s on data socket\n", rsi27, "Asking for %s on data socket\n", rsi27);
        }
        rax34 = strlen(v15, rsi27);
        rdx35 = reinterpret_cast<struct s0*>(&rax34->f1);
        *reinterpret_cast<int32_t*>(&rdi36) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi36) + 4) = 0;
        eax37 = sendto(rdi36, v15, rdx35, 0, reinterpret_cast<int64_t>(rbp3) - 0x251c0, 16);
        v38 = eax37;
        if (v38 < 0) {
            perror("ERROR writing file name", v15, rdx35, "ERROR writing file name", v15, rdx35);
            exit(1, v15, rdx35, 1, v15, rdx35);
        }
        eax39 = time(0);
        eax40 = getpid(0);
        *reinterpret_cast<int32_t*>(&rdi41) = eax40 * eax39;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi41) + 4) = 0;
        srand();
        rand(rdi41, v15, rdi41, v15);
        __asm__("cvtsi2sd xmm0, eax");
        rdi41->f0 = v15->f0;
        rdi42 = rdi41 + 1;
        rsi43 = v15 + 1;
        __asm__("divsd xmm0, xmm1");
        rdi42->f0 = rsi43->f0;
        __asm__("mulsd xmm0, xmm1");
        (rdi42 + 1)->f0 = (rsi43 + 1)->f0;
        do {
            rsi44 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x680);
            *reinterpret_cast<int32_t*>(&rdi45) = v17;
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi45) + 4) = 0;
            v46 = 0x401869;
            eax47 = recvfrom(rdi45, rsi44, 0x5dc, 0, reinterpret_cast<int64_t>(rbp3) - 0x251c0, reinterpret_cast<int64_t>(rbp3) - 0xa4);
            if (eax47 < 0) {
                perror("ERROR receiving file", rsi44, 0x5dc, "ERROR receiving file", rsi44, 0x5dc);
                v46 = 0x401886;
                exit(1, rsi44, 0x5dc, 1, rsi44, 0x5dc);
            }
            r9_48 = reinterpret_cast<struct s2*>(reinterpret_cast<int64_t>(rbp3) - 0x25060);
            r8_49 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x25048);
            peek(eax47, reinterpret_cast<int64_t>(rbp3) - 0x25034, reinterpret_cast<int64_t>(rbp3) - 0x25038, reinterpret_cast<int64_t>(rbp3) - 0x25040, r8_49, r9_48, reinterpret_cast<int64_t>(rbp3) - 0x251a0, v46);
            eax50 = strncmp(reinterpret_cast<int64_t>(rbp3) - 0x680, reinterpret_cast<int64_t>(rbp3) - 0x6f4, 3);
            if (eax50) {
                memcpy(reinterpret_cast<int64_t>(rbp3) - 0x251c7, reinterpret_cast<int64_t>(rbp3) - 0x680, 6);
                rdx51 = reinterpret_cast<struct s0*>(static_cast<int64_t>(eax47 - 6));
                rcx52 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x257b0);
                memcpy(rcx52, reinterpret_cast<int64_t>(rbp3) - 0x680 + 6, rdx51);
                rdi53 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251c7);
                eax54 = atoi(rdi53, reinterpret_cast<int64_t>(rbp3) - 0x680 + 6, rdx51, rcx52, r8_49, r9_48);
                if (v11) {
                    eax55 = v56;
                    *reinterpret_cast<int32_t*>(&r9_48) = *reinterpret_cast<signed char*>(&eax55);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r9_48) + 4) = 0;
                    eax57 = v58;
                    *reinterpret_cast<int32_t*>(&r8_49) = *reinterpret_cast<signed char*>(&eax57);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r8_49) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rsi59) = eax47;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi59) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rdi53) = reinterpret_cast<int32_t>("Message received: %d bytes seq %c%c%c%c%c%c\n");
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi53) + 4) = 0;
                    printf("Message received: %d bytes seq %c%c%c%c%c%c\n", rsi59, "Message received: %d bytes seq %c%c%c%c%c%c\n", rsi59);
                }
                rdx60 = v61;
                rdi53->f0 = socket;
                rsi62 = reinterpret_cast<struct s0*>(4);
                rdi63 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x25050);
                eax64 = drop_message(rdi63, 4);
                if (eax64 && v11) {
                    *reinterpret_cast<uint32_t*>(&rsi62) = eax54;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi62) + 4) = 0;
                    *reinterpret_cast<int32_t*>(&rdi63) = reinterpret_cast<int32_t>("Message %d dropped by the network\n");
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi63) + 4) = 0;
                    printf("Message %d dropped by the network\n", rsi62, "Message %d dropped by the network\n", rsi62);
                }
                if (reinterpret_cast<int32_t>(eax54) < reinterpret_cast<int32_t>(v4 + 100) && !eax64) {
                    v65 = v4;
                    if (reinterpret_cast<int32_t>(eax54) > reinterpret_cast<int32_t>(v4)) {
                        *reinterpret_cast<int32_t*>(&rax66) = eax47;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax66) + 4) = 0;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + reinterpret_cast<int32_t>(eax54 - ((__intrinsic() >> 5) - (reinterpret_cast<int32_t>(eax54) >> 31)) * 100) * 4 - 0x890) = static_cast<int32_t>(rax66 - 6);
                        rsi62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x257b0);
                        rdi63 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x25030 + reinterpret_cast<int32_t>(eax54 - ((__intrinsic() >> 5) - (reinterpret_cast<int32_t>(eax54) >> 31)) * 100) * 0x5d6);
                        memcpy(rdi63, rsi62, static_cast<int64_t>(eax47 - 6));
                        *reinterpret_cast<uint32_t*>(&rax67) = v4;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax67) + 4) = 0;
                        ecx68 = static_cast<int32_t>(rax67 + 1);
                        *reinterpret_cast<int32_t*>(&rdx60) = (__intrinsic() >> 5) - (ecx68 >> 31);
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx60) + 4) = 0;
                        v69 = ecx68 - *reinterpret_cast<int32_t*>(&rdx60) * 100;
                        while (!reinterpret_cast<uint1_t>(reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v69 * 4 - 0x890) < 0) | reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v69 * 4 - 0x890) == 0))) {
                            ++v65;
                            ++v69;
                            if (v69 != 100)
                                continue;
                            v69 = 0;
                        }
                    }
                    if (v33 == 0x1f4) {
                        do {
                            *reinterpret_cast<int32_t*>(&rdx60) = 1;
                            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx60) + 4) = 0;
                            *reinterpret_cast<uint32_t*>(&rsi62) = 0;
                            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi62) + 4) = 0;
                            *reinterpret_cast<int32_t*>(&rdi63) = 0;
                            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi63) + 4) = 0;
                            eax70 = waitpid(0, 0, 1);
                        } while (eax70 != -1);
                        v33 = 0;
                    }
                    eax71 = fork(rdi63, rsi62, rdx60);
                    if (eax71 < 0) {
                        perror("ERROR creating process", rsi62, rdx60);
                        exit(1, rsi62, rdx60);
                    }
                    if (!eax71) {
                        *reinterpret_cast<uint32_t*>(&rdx72) = v65;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx72) + 4) = 0;
                        sprintf(reinterpret_cast<int64_t>(rbp3) - 0x251d8, "%06d", rdx72);
                        strncpy(reinterpret_cast<int64_t>(rbp3) - 0x251d1, reinterpret_cast<int64_t>(rbp3) - 0x6f8, 4);
                        rsi62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251d8);
                        rdi73 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251d1);
                        strcat(rdi73, rsi62);
                        eax74 = rand(rdi73, rsi62);
                        __asm__("cdq ");
                        *reinterpret_cast<int32_t*>(&rdi75) = reinterpret_cast<int32_t>(eax74) % 0x4e20 + 0x2710;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi75) + 4) = 0;
                        usleep(rdi75, rsi62);
                        eax76 = rand(rdi75, rsi62);
                        *reinterpret_cast<int32_t*>(&rdx77) = (__intrinsic() >> 5) - (reinterpret_cast<int32_t>(eax76) >> 31);
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx77) + 4) = 0;
                        if (v11) {
                            rsi62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251d1);
                            printf("Sent %s\n", rsi62, "Sent %s\n", rsi62);
                        }
                        __asm__("cvtsi2sd xmm0, dword [rbp-0x84]");
                        __asm__("pxor xmm1, xmm1");
                        __asm__("ucomisd xmm0, xmm1");
                        if (v11 <= 0) {
                            if (v11) {
                                rsi62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251d1);
                                printf("%s dropped by network\n", rsi62, "%s dropped by network\n", rsi62);
                            }
                        } else {
                            rax78 = strlen(reinterpret_cast<int64_t>(rbp3) - 0x251d1, rsi62);
                            rdx77 = reinterpret_cast<struct s0*>(&rax78->f1);
                            rsi62 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251d1);
                            *reinterpret_cast<int32_t*>(&r9_48) = 16;
                            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&r9_48) + 4) = 0;
                            r8_49 = reinterpret_cast<struct s0*>(reinterpret_cast<int64_t>(rbp3) - 0x251c0);
                            *reinterpret_cast<int32_t*>(&rdi79) = v17;
                            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi79) + 4) = 0;
                            eax80 = sendto(rdi79, rsi62, rdx77, 0, r8_49, 16);
                            v38 = eax80;
                        }
                        if (v38 < 0) {
                            perror("ERROR sending ACK", rsi62, rdx77, "ERROR sending ACK", rsi62, rdx77);
                            exit(1, rsi62, rdx77, 1, rsi62, rdx77);
                        }
                        exit(0, rsi62, rdx77, 0, rsi62, rdx77);
                    }
                    ++v33;
                    *reinterpret_cast<uint32_t*>(&rax81) = v4;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax81) + 4) = 0;
                    ecx82 = static_cast<int32_t>(rax81 + 1);
                    *reinterpret_cast<int32_t*>(&rdx60) = (__intrinsic() >> 5) - (ecx82 >> 31);
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx60) + 4) = 0;
                    v83 = ecx82 - *reinterpret_cast<int32_t*>(&rdx60) * 100;
                    while (!reinterpret_cast<uint1_t>(reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v83 * 4 - 0x890) < 0) | reinterpret_cast<uint1_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v83 * 4 - 0x890) == 0))) {
                        rdx84 = reinterpret_cast<struct s0*>(static_cast<int64_t>(*reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v83 * 4 - 0x890)));
                        eax85 = fwrite(reinterpret_cast<int64_t>(rbp3) - 0x25030 + v83 * 0x5d6, 1, rdx84, v29, r8_49, r9_48);
                        v32 = v32 + eax85;
                        eax86 = ftell(v29, 1, rdx84, v29, r8_49, r9_48);
                        if (eax86 != v32) {
                            perror("ERROR on file position indicator\n", 1, rdx84, "ERROR on file position indicator\n", 1, rdx84);
                            exit(1, 1, rdx84, 1, 1, rdx84);
                        }
                        *reinterpret_cast<uint32_t*>(&rsi62) = 0;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi62) + 4) = 0;
                        fseek(v29, 0, 2, v29, r8_49, r9_48);
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(rbp3) + v83 * 4 - 0x890) = 0;
                        ++v4;
                        *reinterpret_cast<uint32_t*>(&rax87) = v4;
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax87) + 4) = 0;
                        ecx88 = static_cast<int32_t>(rax87 + 1);
                        *reinterpret_cast<int32_t*>(&rdx60) = (__intrinsic() >> 5) - (ecx88 >> 31);
                        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx60) + 4) = 0;
                        v83 = ecx88 - *reinterpret_cast<int32_t*>(&rdx60) * 100;
                    }
                    continue;
                }
            } else {
                do {
                    *reinterpret_cast<int32_t*>(&rdx60) = 1;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdx60) + 4) = 0;
                    *reinterpret_cast<uint32_t*>(&rsi62) = 0;
                    *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi62) + 4) = 0;
                    eax89 = waitpid(0, 0, 1);
                } while (eax89 != -1);
                fclose(v29, 0, 1);
                v31 = 0;
                if (!v11)
                    continue;
            }
            puts("Received FIN", 0, 1);
        } while (v31);
        if (v11) {
            *reinterpret_cast<uint32_t*>(&rsi62) = v32;
            *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rsi62) + 4) = 0;
            printf("Total bytes received %d\n", rsi62, "Total bytes received %d\n", rsi62);
        }
        *reinterpret_cast<int32_t*>(&rdi90) = v17;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rdi90) + 4) = 0;
        close(rdi90, rsi62, rdx60);
        *reinterpret_cast<int32_t*>(&rax91) = 0;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax91) + 4) = 0;
    } else {
        *reinterpret_cast<int32_t*>(&rax91) = -1;
        *reinterpret_cast<int32_t*>(reinterpret_cast<int64_t>(&rax91) + 4) = 0;
    }
    return rax91;
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

void fun_400de6() {
    goto 0x400c30;
}

void fun_400e56() {
    goto 0x400c30;
}

void fun_400d96() {
    goto 0x400c30;
}

void fun_400db6() {
    goto 0x400c30;
}

void fun_400d56() {
    goto 0x400c30;
}

void fun_400c86() {
    goto 0x400c30;
}

void fun_400d16() {
    goto 0x400c30;
}

void fun_400d76() {
    goto 0x400c30;
}

void fun_400da6() {
    goto 0x400c30;
}

void fun_400c96() {
    goto 0x400c30;
}

void fun_400d46() {
    goto 0x400c30;
}

void fun_400df6() {
    goto 0x400c30;
}

void fun_400c46() {
    goto 0x400c30;
}

void fun_400e46() {
    goto 0x400c30;
}

void fun_400d86() {
    goto 0x400c30;
}

void fun_400d26() {
    goto 0x400c30;
}

void fun_400d66() {
    goto 0x400c30;
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

void fun_400c76() {
    goto 0x400c30;
}

void fun_400c56() {
    goto 0x400c30;
}

void fun_400e26() {
    goto 0x400c30;
}

void fun_400e16() {
    goto 0x400c30;
}

void fun_400d36() {
    goto 0x400c30;
}

void fun_400d06() {
    goto 0x400c30;
}

void fun_400cd6() {
    goto 0x400c30;
}
