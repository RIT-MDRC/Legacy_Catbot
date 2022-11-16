<img src="https://pbs.twimg.com/profile_images/661962002/logo_400x400.png" align="right" alt="MDRC LOGO" title="MDRC LOGO" width="100">

# Catbot

> Quadruped Hybrid Pneumatic-Electric Robot. Utilizes McKibben Muscles for bio-inpired locomotion.

# Table of Contents

1. [Getting Started](#getting-started)
2. [List of Dependent Libraries](#list-of-necessary-libraries)
3. [Setup](#setup)
4. [How to Download Libraries](#downloading-necessary-library-using-platformio)
5. [Get Help](#help)
6. [For Common Issues](#note)

# Getting Started

-   Clone git
-   Install PlatformIO Extension
-   Download Libraries in PlatformIO Library

More detailed instructions below

# List of Necessary Libraries

-   Encoder by Paul Stoffregen
-   Servo by Michael Margolis
-   EventAnalog by philip Fletcher

Last updated: 10/2/22 by Hiroto Takeuchi

## Setup for VSCode + PlatformIO

-   Install and Open Visual Studio Code
-   Install PlatformIO extensions
-   Create a new folder with the name of your choice
-   Clone repository
    - open folder in vscode and open terminal with ctrl+` or in the terminal
    ```
    cd /folder_of_choice
    git clone https://github.com/RIT-MDRC/Catbot.git .
    ```
-   Switch into encoder_test branch (temporary; until merge of this branch)
    -   In the bottom blue banner, click on "main"
    -   select "origin/encoder-test"

## Downloading Necessary Library using PlatformIO

-   Open PlatformIO home
    > Click on the alien head on the left.
    > Go to QUICK ACCESS > PIO Home > Open
-   Open "Libraries" on the left menu
-   In the search bar, search for [necessary Libraries](#list-of-necessary-libraries)

### Note

-   On extension conflict error (at least that Hiro encountered)
    > Disable/uninstall arduino extension due to conflicts with PIO extension
