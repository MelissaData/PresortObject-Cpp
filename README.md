# Melissa - Presort Object Windows C++

## Purpose
This code showcases the Melissa Presort Object using C++.

Please feel free to copy or embed this code to your own project. Happy coding!

For the latest Melissa Presort Object release notes, please visit https://releasenotes.melissa.com/on-premise-api/presort-object/

For further details, please visit: https://docs.melissa.com/on-premise-api/presort-object/presort-object-quickstart.html

The console will ask the user for:

- A csv file that contains addresses you would like to presort

And return 

- A csv file of presorted addresses

## Tested Environments
- Windows 10 64-bit Microsoft Visual C++ 14.34, Powershell 5.1
- Melissa data files for 2024-05
- Nmake 14.34
- Visual Studio 2022 Developer Command Prompt v17.4.2 64-bit

## Required File(s) and Programs

#### mdPresort.dll
This is the c++ code of the Melissa Object.

#### Data File(s) 
- mdL004A.dat
- mdL004B.dat
- mdL004C.dat
- mdL005.dat
- mdL006A.dat
- mdL006B.dat
- mdL007.dat
- mdL008.dat
- mdL009A.dat
- mdL009B.dat
- mdL010.dat
- mdL011A.dat
- mdL011B.dat
- mdL012.dat
- mdL201A.dat
- mdL201B.dat
- mdL601.dat
- mdL602.dat
- mdL801A.dat
- mdL801B.dat
- mdPresort.lic
- mdValid5.dat
- PostalRatesFile.txt
- 3600r_T.pdf
- 3602c_T.pdf
- 3602n_T.pdf
- 3602r_T.pdf
- 8125_T.pdf
- mdCityState.dat
- mdDSF.DAT
- mdL001.dat
- mdL002A.dat
- mdL002B1.dat
- mdL002B2.dat
- mdL002C.dat

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

#### Visual Studio Developer Command Prompt
It is important to note that you must be able to initialize the Visual Studio Developer Command Prompt environment for `x86_x64` in order to test the Melissa Presort Object. The Visual Studio Developer Command Prompt should already be downloaded if you have Microsoft Visual Studio installed. 

To check if you are able to intialize the Visual Studio Developer Command Prompt for `x86_x64`, you can open the start menu and search for `x86_x64 Cross Tools Command Prompt for VS 2022`. If this program exists, then you may continue to the next steps.

Alternatively, you can check to see if the following filepath exists: `C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat` (with Visual Studio 2022 installed). If the filepath exists, then you may continue to the next steps.

#### Set up Powershell settings
If running Powershell for the first time, you will need to run this command in the Powershell console: `Set-ExecutionPolicy RemoteSigned`.
The console will then prompt you with the following warning shown in the image below. 
 - Enter `'A'`. 
 	- If successful, the console will not output any messages. (You may need to run Powershell as administrator to enforce this setting).
	
 ![alt text](/screenshots/powershell_executionpolicy.png)

#### Download this project
```
$ git clone https://github.com/MelissaData/PresortObject-Cpp
$ cd PresortObject-Cpp
```

#### Set up Melissa Updater 
Melissa Updater is a CLI application allowing the user to update their Melissa applications/data. 

- Download Melissa Updater here: <https://releases.melissadata.net/Download/Library/WINDOWS/NET/ANY/latest/MelissaUpdater.exe>
- Create a folder within the cloned repo called `MelissaUpdater`.
- Put `MelissaUpdater.exe` in `MelissaUpdater` folder you just created.

#### Different ways to get data file(s)
1.  Using Melissa Updater
    - It will handle all of the data download/path and dll(s) for you. 
2.  If you already have the latest release zip, you can find the data file(s) in there
    - To pass in your own data file path directory, you may either use the '-dataPath' parameter or enter the data file path directly in interactive mode.
    - Comment out this line "DownloadDataFiles -license $License" in the powershell script.
    - This will prevent you from having to redownload all the files.

## Run Powershell Script
Parameters:
- -file: a test file
 	
  This is convenient when you want to get results for a specific file in one run instead of testing multiple files in interactive mode.

- -dataPath (optional): a data file path directory to test the Presort Object
- -license (optional): a license string to test the Presort Object
- -quiet (optional): add to the command if you do not want to get any console output from the Melissa Updater

When you have modified the script to match your data location, let's run the script. There are two modes:
- Interactive 

    The script will prompt the user for a file path, then use the provided file to test Presort Object.  For example:
    ```
    $ .\MelissaPresortObjectWindowsCpp.ps1
    ```
    For quiet mode:
    ```
    $ .\MelissaPresortObjectWindowsCpp.ps1 -quiet
    ```
- Command Line 

    You can pass a file path in ```-file``` parameter and a license string in ```-license``` parameter to test Presort Object. For example:
    ```
    $ .\MelissaPresortObjectWindowsCpp.ps1 -file ".\MelissaPresortObjectSampleInput.csv" 
    $ .\MelissaPresortObjectWindowsCpp.ps1 -file ".\MelissaPresortObjectSampleInput.csv" -license "<your_license_string>"
    ```
    For quiet mode:
    ```
    $ .\MelissaPresortObjectWindowsCpp.ps1 -file ".\MelissaPresortObjectSampleInput.csv" -quiet
    $ .\MelissaPresortObjectWindowsCpp.ps1 -file ".\MelissaPresortObjectSampleInput.csv" -license "<your_license_string>" -quiet
    ```
This is the expected output from a successful setup for interactive mode:

![alt text](/screenshots/output.png)

    
## Troubleshooting
Troubleshooting for errors found while running your program.

### C# Errors:
| Error      | Description |
| ----------- | ----------- |
| ErrorRequiredFileNotFound      | Program is missing a required file. Please check your Data folder and refer to the list of required files above. If you are unable to obtain all required files through the Melissa Updater, please contact technical support below. |
| ErrorLicenseExpired   | Expired license string. Please contact technical support below. |


## Contact Us
For free technical support, please call us at 800-MELISSA ext. 4 (800-635-4772 ext. 4) or email us at tech@melissa.com.

To purchase this product, contact the Melissa sales department at 800-MELISSA ext. 3 (800-635-4772 ext. 3).
