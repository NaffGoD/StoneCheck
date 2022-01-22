# StoneCheck
This program is designed to get information about the processor.
So, as mentioned above, we can use the capabilities of this program to get many parameters. Here is a list of them:

  • Specification - the so-called "CPU string" of the processor. This is the string that stores its name. The next line indicates the CPUID - a command that gives three values ​​-   Family, Model and Stepping, which can determine the core and revision of the CPU core.
  
  • Company - a ribbon that indicates the manufacturer of this processor. Most often the manufacturer is GenuineIntel, less AuthenticAMD and others.
  
  • Instructions - lists instruction sets supported by the processor, such as MMX, SSE and others. In this window, next to each such special instruction, there are two parameters:   "Yes" and "No", which are responsible for demonstrating whether a particular processor supports it.
  
  • Cashe memory - A parameter that defines a summary of CPU cache capacity and displays it in megabytes (MB).
  
  • Processor Base Frequency - the base frequency of the processor. This is usually the frequency without Turbo Boost mode, which is average when performing system operations and   calculations within it.
  
  • Processor Max Frequency - the maximum frequency of the processor that it can reach without additional external overclocking. At this clock speed, you can see the fastest speed   in performing any manipulations on the computer.
  
  • Processor Bus Frequency - the external frequency of the processor, which is the (reference) frequency of the processor bus.
  
  • Cores - shows the number of active CPU cores. For example: my processor is quad-core, so the number of cores is four. However, kernels can be either disabled or (sometimes)     activated disabled by the manufacturer, so the number in this field may differ from the initial settings. Because each kernel has its own cache, the number of active kernels       affects other items.
  
  • Threads - the number of logical processors in the system or the number of threads. It differs from the number of active cores in the presence of Hyperthreading technology,       which allows you to run multiple threads on a single processor core, which is defined by the system as the presence of additional virtual (logical) cores. Currently, the           technology allows you to run two threads on the kernel, so the number of threads on such a processor will be twice the number of cores. 
