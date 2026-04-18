## Power Violence Edition

### Overall Introduction of This Project
* This project is designed to create the `Power Violence Edition`, including its rules and procedures. 
* This project has not yet been fully completed. The main part of the project's program has not been fully built.(In fact, it is almost empty.) The version of the project's rules is **0.0.19**.

### Specific Implementation of This Project
* The implementation of this project is placed in the **src** directory. **PowerViolenceObjects** is a set of data types in `PV`, mainly written in **C**. The **PowerViolence** directory contains the program implementation of `PV`, mainly written in **Python**.
* The rules section of this project includes the general rules and update announcements. The general rules are written in **Markdown** and are converted into a **PDF** file. The update announcements are also written in **Markdown**, but no **PDF** file is generated. Some pictures and the corresponding **Python** files for generating those pictures are also included in the rules section.
* The testing section of this project is located in the **tests** directory. The **ctests** directory mainly contains tests for **PowerViolenceObjects**, and the **pytests** directory mainly contains tests for **PowerViolence**.
* This project also includes a simple implementation, named **PowerViolence_simplified**, which does not fully implement the rules and can only allow one player and one computer to play against each other. This file is a **macOS** executable file.

* If you want to learn how to play this game, you can look at *rule/PV_rule.png*. (In fact, it's almost Chinese)

> Thanks to https://github.com/KaSui2333/PdfToImg.git for providing the program for converting PDF to PNG.
