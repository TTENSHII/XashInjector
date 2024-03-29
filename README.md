<div align="center">
  <h1>Xash Injector</h1>
</div>

<details>
<summary>Table of Contents</summary>

## :blue_book: Index

- [About](#space_invader-about)
- [Example](#flower_playing_cards-example)
- [Usage](#flags-usage)
- [Installation](#package-installation)
- [Development](#wrench-development)
- [Contribution & Guideline](#cherry_blossom-contribution--guideline)
- [Branches & PR](#cactus-branches--pr)
- [Making mods](#gem-Making-mods)
- [Resources](#page_facing_up-resources)
- [Usage Guidelines](#lock-usage-guidelines)

</details>

## :space_invader: About
Xash is a C++ mono injector built upon the WinAPI.
It enables the injection of assemblies (such as .NET DLLs) into a selected process, providing a flexible solution to enhance and extend functionality.
Designed primarily for 64-bit applications, there are plans to extend support to 32-bit applications.

##  :flower_playing_cards: Example
![image](https://github.com/TTENSHII/XashInjector/assets/87119012/c685003e-ef73-4436-aa92-3ebc5b1c102a)

## :flags: Usage

- **Launching Xash:**
  - Execute the Xash binary.
  - Choose the target process.
  - Select the DLL assemblies.
  - Fill in the necessary namespace, class, and load method (corresponding to the desired mod).
  - Click the "Inject" button to complete the process.
  - Multiple assemblies can be injected simultaneously.
  - You can eject or see injected assemblies in the Loaded Dll panel.

- **Assembly Desinjection:**
  - Navigate to the "Loaded dll" panel.
  - Click the "Eject" button of the correct assemblies.

## :sparkles: Themes
You can configure the application theme.
You can choose from a range of predefined themes or colour-by-colour themes.
For the moment, the theme is not saved; this feature is coming on the json-save branch.

![Arcade](https://github.com/TTENSHII/XashInjector/assets/87119012/5c23fdc9-3176-4c5f-9bf0-66eba2fec862)
![BW](https://github.com/TTENSHII/XashInjector/assets/87119012/ad809c2c-2937-4a30-99d3-1e1c1b4d4a27)
![Purple](https://github.com/TTENSHII/XashInjector/assets/87119012/5061537e-a385-4a31-bf0d-68c33dfb4528)
![Default](https://github.com/TTENSHII/XashInjector/assets/87119012/1f22363d-8eb0-418e-9b78-fcd19875ee64)
![Ocean](https://github.com/TTENSHII/XashInjector/assets/87119012/84084461-64b2-4fda-948b-d8ffc17f1757)

## :package: Installation

- **Obtaining Binaries:**
  - Download the precompiled binaries from the [GitHub releases page](https://github.com/TTENSHII/XashInjector/releases).

- **Compilation Instructions:**
  - Developers can also compile the project by following the instructions provided in the development section.

- **Supported Operating System:**
  - Xash only works on Windows.

- **System Architecture:**
  - Xash currently exclusively supports 64-bit applications.

## :wrench: Development

Developers have the flexibility to use the compiler and the Win SDK of their choice.
However, for reference, the project is developed using the following tools:
- MSVC v143
- Windows 11 SDK 10.0.22621.0
- CMake

In the "scripts" directory, you'll find compilation scripts.
Alternatively, if you prefer a custom approach, you can use your own CMake commands. For example:
```powershell
cmake -S . -B build
cmake --build build --config Release -- /m
```

Feel free to adapt these tools and commands to your development environment as needed.

### :memo: Clone the repository

Clone the repository with submodules:
```powershell
git clone --recursive https://github.com/TTENSHII/XashInjector
```

If you have already cloned the repository, you can do this to add submodules:
```powershell
git submodule update --init --recursive
```

###  :file_folder: File Structure

```
├── assets
├── .github
│   └── workflows
├── scripts
│   ├── build-release
│   └── build-debug
├── external (the project's git sub-modules)
│   ├── imgui
│   └── CMakeLists.txt
├── src
│   ├── GUI
│   │   ├── Imgui
│   │   ├── Dx11
│   │   ├── WindowManager
│   │   ├── Gui-components
│   │   ├── CMakeLists.txt
│   │   └── GUI-related files
│   ├── injector
│   │   ├── Assembly
│   │   ├── Mono-Module
│   │   ├── Injector-utilities
│   │   └── CMakeLists.txt
│   └── system
│       ├── CMakeLists.txt
│       └── System-related files
├── CMakeLists.txt
├── .gitignore
├── .gitmodules
├── .clang-format
└── README.md
```

## :cherry_blossom: Contribution & Guideline

Welcome to the XashInjector project! We appreciate your interest in contributing. To get started, here are some guidelines:

- **Issues and Discussions:**
  - Feel free to explore our [Issues](https://github.com/TTENSHII/XashInjector/issues) for existing tasks or report new ones.
  - Engage in Discussions [here](https://github.com/TTENSHII/XashInjector/discussions) to ask questions or propose ideas.

- **Contributing Basics:**
  - Familiarize yourself with the project's codebase.
  - Submit issues for bug reports, feature requests, or discussions before diving into code changes.

- **Coding Style:**
  - Please follow the established coding style, respecting conventions such as `mClassMember` or pascalCase for methods, for example.
  - Ensure compliance with `.clang-format` and maintain the project structure.

- **Getting Started:**
  - Clone the repository with git submodules.
  - Read Development section
  - See Branches & PR section for more informations.

### :cactus: Branches & PR

**Branching Workflow:**

  - **`main`**: The production branch.
  - **`dev`**: The development branch.
  - No other permanent branches will be created in the repository; all branches must be merged with the `main` branch.

**Creating a New Branch:**

  - When initiating work on a new feature, create a branch with a concise and clear name, such as `support-of-32bits`, `best-gui-theme` or `fix-settings-panel`.
  - Aim for brevity and clarity in branch naming.

**Creating a Pull Request:**

  - Submit the pull request (PR) in the `dev` branch.
  - Provide a detailed description of the changes made.
  - Add correct labels such as `bug fix`, `enhancement`, `GUI`, `documentation`...
  - Ensure the PR passes all continuous integration checks and receives positive feedback.
  - After successful checks and approval, the changes will be merged.

## :gem: Making mods
While I won't provide an in-depth tutorial on mod creation, here are some essential tips for beginners:

  - **C# .NET development:**
Have knowledge of C# or other object-oriented programming languages.
Install tools to compile the code into a dll Class Library (.NET Framework).

  - **Mod Project Setup:**
When initiating your mod project, choose "Class Library (NET Framework)."
Make sure that the .NET Framework version is the same of the targeted game.
You can usually find this information in the game files.

  - **Resource Exploration:**
Explore mod development through various resources.
Watch videos, read articles, or participate in forums dedicated to modding.
Enjoy the learning process and have fun experimenting with your creations!

##  :page_facing_up: Resources

- [**dnSpy**](https://github.com/dnSpy/dnSpy): dnSpy is a powerful tool for .NET assembly editing and debugging.
It provides a user-friendly interface for examining and modifying assemblies, making it an excellent companion for creating mods in games using Mono.

- [**Dear ImGui**](https://github.com/ocornut/imgui): ImGui is a highly versatile and efficient graphical user interface library,
offering an easy way to create user interfaces in applications/mods.

##  :lock: Usage Guidelines

Ensure compliance with the terms of use for other programs when utilizing Xash.
Exercise caution to avoid inappropriate use, such as injecting mods in multiplayer environments,
and adhere to the rules and regulations of respective communities.
