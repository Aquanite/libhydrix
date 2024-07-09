extern void kernel_main();  // Real kernel function.

extern "C" void hydrix_main()
{
    // Begin initialization of devices.
    

    kernel_main();
    while (true);
}