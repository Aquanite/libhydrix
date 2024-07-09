#include <libhydrix/hsyscall/syscall.h>
#include <libhydrix/hmouse/mouse.h>
#include <libhydrix/hkey/keyboard.h>
#include <libhydrix/hgl/graphics.h>
Console* syscall_console;

void syscall_init(Console* con)
{
    syscall_console = con;
}
void handle_syscall(registers_t *r)
{
    if (r->rax == 1)
    {
        if (r->rbx == 0)
        {
            syscall_console->ClearS();
        }
        else if (r->rbx == 1)
        {
            syscall_console->WriteS((char*)r->rcx, (int)r->rdx); //rcx is the address of the string, rdx is the color
        }
        else if (r->rbx == 2)
        {
            syscall_console->WriteLineS((char*)r->rcx, (int)r->rdx); //rcx is the integer, rdx is the color
        }
    }
    else if (r->rax == 2)
    {
        switch (r->rbx)
        {
        case 0:
            syscall_console->graphics->swap();
            break;
        case 1:
            syscall_console->graphics->clear();
            break;
        case 2:
            if (r->rcx < syscall_console->graphics->width && r->rdx < syscall_console->graphics->height) {
                syscall_console->graphics->SwapBuffer[r->rdx * (syscall_console->graphics->pitch / 4) + r->rcx] = r->rsi;
            }
            break;
        case 3:
            syscall_console->graphics->put_line(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 4:
            syscall_console->graphics->put_rect(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 5:
            syscall_console->graphics->put_filled_rect(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 6:
            syscall_console->graphics->put_circle(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 7:
            syscall_console->graphics->put_filled_circle(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 8:
            syscall_console->graphics->put_char(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 9:
            syscall_console->graphics->put_string((char*)r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 10:
            BMPI Image;
            Image.width = r->rcx;
            Image.height = r->rdx;
            Image.data = (int*)r->rsi;
            syscall_console->graphics->put_image(r->r8, r->r9, Image);
            break;
        case 11:
            BMPA AImage;
            AImage.width = r->rcx;
            AImage.height = r->rdx;
            AImage.data = (long*)r->rsi;
            syscall_console->graphics->put_image_alpha(r->r8, r->r9, AImage);
            break;
        case 12:
            BMPI SImage;
            SImage.width = r->rcx;
            SImage.height = r->rdx;
            SImage.data = (int*)r->rsi;
            syscall_console->graphics->put_image_stretch(r->r8, r->r9, r->r10, r->r11, SImage);
            break;
        case 13:
            BMPA SAImage;
            SAImage.width = r->rcx;
            SAImage.height = r->rdx;
            SAImage.data = (long*)r->rsi;
            syscall_console->graphics->put_image_stretch_alpha(r->r8, r->r9, r->r10, r->r11, SAImage);
            break;
        case 14:
            syscall_console->graphics->put_pixel_alpha(r->rcx, r->rdx, r->rsi);
            break;
        }

    }
    else if (r->rax == 3)
    {
        switch (r->rbx)
        {
            case 0:
                //use kalloc
                r->rax = (uint64_t)kalloc(r->rcx);
                break;
            case 1:
                //use kfree
                kfree((void*)r->rcx);
                break;
            case 2:
                //kcalloc
                r->rax = (uint64_t)kcalloc(r->rcx);
                break;
            case 3:
                //krealloc
                r->rax = (uint64_t)krealloc((void*)r->rcx, r->rdx);
                break;
        }
    }
    return;
}