#include <libhydrix/hsyscall/syscall.h>
#include <libhydrix/hmouse/mouse.h>
#include <libhydrix/hkey/keyboard.h>
#include <libhydrix/hgl/graphics.h>
Console* syscall_console;

void InitializeSyscall(Console* con)
{
    syscall_console = con;
}
void HandleSyscall(registers_t *r)
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
            syscall_console->graphics->Display();
            break;
        case 1:
            syscall_console->graphics->Clear();
            break;
        case 2:
            if (r->rcx < syscall_console->graphics->Width && r->rdx < syscall_console->graphics->Height) {
                syscall_console->graphics->SwapBuffer[r->rdx * (syscall_console->graphics->Pitch / 4) + r->rcx] = r->rsi;
            }
            break;
        case 3:
            syscall_console->graphics->DrawLine(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 4:
            syscall_console->graphics->DrawRectangle(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 5:
            syscall_console->graphics->DrawFilledRectangle(r->rcx, r->rdx, r->rsi, r->rdi, r->r8);
            break;
        case 6:
            syscall_console->graphics->DrawCircle(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 7:
            syscall_console->graphics->DrawFilledCircle(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 8:
            syscall_console->graphics->DrawChar(r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 9:
            syscall_console->graphics->DrawString((char*)r->rcx, r->rdx, r->rsi, r->rdi);
            break;
        case 10:
            BMPI Image;
            Image.width = r->rcx;
            Image.height = r->rdx;
            Image.data = (int*)r->rsi;
            syscall_console->graphics->DrawImage(r->r8, r->r9, Image);
            break;
        case 11:
            BMPA AImage;
            AImage.width = r->rcx;
            AImage.height = r->rdx;
            AImage.data = (long*)r->rsi;
            syscall_console->graphics->DrawAlphaImage(r->r8, r->r9, AImage);
            break;
        case 12:
            BMPI SImage;
            SImage.width = r->rcx;
            SImage.height = r->rdx;
            SImage.data = (int*)r->rsi;
            syscall_console->graphics->DrawStretchedImage(r->r8, r->r9, r->r10, r->r11, SImage);
            break;
        case 13:
            BMPA SAImage;
            SAImage.width = r->rcx;
            SAImage.height = r->rdx;
            SAImage.data = (long*)r->rsi;
            syscall_console->graphics->DrawStretchedAlphaImage(r->r8, r->r9, r->r10, r->r11, SAImage);
            break;
        case 14:
            syscall_console->graphics->DrawAlphaPixel(r->rcx, r->rdx, r->rsi);
            break;
        }

    }
    return;
}