# 2장: Ramdisk 디바이스 드라이버 구현

Ramdisk는 디바이스 드라이버를 제작하는 가장 기초적인 과정으로 이번 챕터를 통해서 MQ 블록 레이어 기반 Ramdisk를 생성해보도록 하겠습니다.

## 설치해야 할 것

다음 명령어를 통해서 필요한 프로그램을 추가로 다운받도록 합니다.

```bash
sudo apt update -y
sudo apt install -y clang-format
```

## HelloWorld

먼저 Makefile은 다음과 같이 작성을 해주시면 됩니다.

```make
obj-m += ramdisk.o
KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules

format:
	clang-format -i *.c

clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
```

`obj-m`에서도 알 수 있듯이, 파일 이름은 `ramdisk.c` 파일로 설정을 해주도록 합니다.

각각 명령은 다음을 실행합니다.

```bash
make all # 리눅스 커널 모듈을 생성을 합니다.
make format # 소스 코드에 대한 포맷팅을 실시합니다.
make clean # 리눅스 커널 모듈의 파생 파일을 삭제하는데 사용합니다.
```

그리고 다음과 같은 파일을 작성합니다.

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init blk_ram_init(void) {
    int ret = 0;
    printk(KERN_INFO "hello world\n");
    return ret;
}

static void __exit blk_ram_exit(void)
{
    printk(KERN_INFO "bye bye!!\n");
}

module_init(blk_ram_init);
module_exit(blk_ram_exit);

MODULE_AUTHOR("BlaCkinkGJ");
MODULE_LICENSE("GPL");
```

이 다음에 다음 명령어를 실행해주도록 합시다.

```bash
sudo insmod ramdisk.ko
```

> 만약에 `sudo dmesg`를 해서 문제가 발생했으면 다음 명령어를 실행해본다.
> 문제 내용: "module: x86/modules: Skipping invalid relocation target, existing value is nonzero for type 1"

```bash
sudo apt update && sudo apt upgrade
sudo apt remove --purge linux-headers-*
sudo apt autoremove && sudo apt autoclean
sudo apt install linux-headers-generic
sudo reboot
```

그리고 다음 명령어를 수행하고 dmesg 결과를 확인하도록 합니다.

```bash
sudo rmmod ramdisk.ko
sudo dmesg
```

그러면 "hello world"와 "bye bye!!"가 정상적으로 나타남을 확인할 수 있습니다.

> 들어가야 할 내용
>
> 1. 어떻게 Ramdisk 디바이스 드라이버를 만들지
> 2. 파일 시스템 실제 적용
> 3. 사용자 프로그램의 생성
> 4. printk 및 ftrace 사용법
> 5. eBPF를 통한 탐치

## 참고 자료

- https://blog.pankajraghav.com/2022/11/30/BLKRAM.html
- https://github.com/Panky-codes/blkram
- https://github.com/rprata/linux-device-driver-tutorial/tree/master
