# twentyONE HR Management Application

<div align="center">

<a href="">![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)</a>
<a href="">![MySQL](https://img.shields.io/badge/mysql-4479A1.svg?style=for-the-badge&logo=mysql&logoColor=white)</a>
<a href="">![Docker](https://img.shields.io/badge/docker-%230db7ed.svg?style=for-the-badge&logo=docker&logoColor=white)</a>

</div>

## What is twntyOne HR Management Application?
twentyOne HR Management is an application designed to streamline and enhance the efficiency of human resources (HR) departments. It provides a comprehensive suite of tools for managing various HR functions, including employee records, working hours, and request handling


## Deployment Guide

### 1.	Clone git project
<br>
git clone https://github.com/MehmetMertt/twentyONE_HR_System.git<br>
cd twentyONE_HR_System<br>
cd Database<br>
docker compose up -d<br>
cd ..<br>
cd HR_Managment_System_Application<br>
mkdir build<br>

### 2.	Create Database<br>
After that we need to create the database. Visit localhost:8080 and login using the default credential<br>
Username: root<br>
Password: admin<br>
choose the database and navigate to the SQL Tab<br>
And insert the hrmgt_create.sql into the databse<br>

### 3.	Build project and create exe<br>
Now use the Qt 6.7.0 (MinGW) that is installed after installing Qt 6.7.0  <br>

cd <into cloned folder>\HR_Managment_System_Application\build<br>
qmake ..\HR_Managment_System_Application.pro -spec win32-g++<br>
mingw32-make.exe -j4<br>
cd release<br>
windeployqt .<br>
cd ..<br>
mingw32-make.exe clean -j4<br>
move ..\..\Database\libmysql.dll .\release<br>
move ..\..\Database\qsqlmysql.dll .\release\sqldrivers<br>


Now you can use the files in the release folder for your deployment. And the exe is executable and will start the Application.<br>
Please refrain from using any real credentials, passwords, or sensitive information, as this is a school project not intended to store valuable data.
<br>
Thank you!!!
