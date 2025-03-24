#!/bin/bash

BackupDir="/home/$USER/Backup" // название директории, где лежит Backup
ReportFile="/home/$USER/Backup/.backup_report" // файл backup_report
SourceDir="/home/$USER/source" // название директории, где лежит source

if ! [[ -d "$BackupDir" ]]
then
        mkdir $BackupDir
        fi
if ! [[ -d "$SourceDir" ]]
then
        mkdir $SourceDir
        fi
if ! [[ -f "$ReportFile" ]]
then
        touch $ReportFile
        fi

currentDate=$(date '+%Y-%m-%d')
// ls -1 (отображать файл в 1 строку)
// grep -E "^Backup-*" (искать шаблон)
// cut -d "-" (вместо пробела я сама устанавливаю разделитель) -f 2,3,4 (перечень полей для вырезания.)
// sort -n -r (сортировать по числовому значению в обратном порядке)
// head -1 (вывести первую строку)

// в целом, lastBackupDate нам дает время, когда был создан каталог последний каталог Backup-YYYY-MM-DD
lastBackupDate=$(ls -1 "$BackupDir/" | grep -E "^Backup-*" | cut -d "-" -f 2,3,4 | sort -n -r | head -1)

// в целом, lastBackupDir директорию и время создания каталога Backup-YYYY-MM-DD
// sort -k3,4 - sort будет сортировать на основе полей со 2 по 5, которые считаются все вместе как один ключ сортировки.
lastBackupDir=$(ls -1  "$BackupDir/" | grep -E "^Backup-*" | cut -d "-" -f 1,2,3,4 | sort -n -r -k3,4 | head -1)

// date -d "$currentDate" "+%s" вывод даты по указанной строке (например 'yesterday', 'tomorrow', 'last monday').
currentDateSec=$(date -d "$currentDate" "+%s")
lastBackupDateSec=$(date -d "$lastBackupDate" "+%s")

// вот тут мы вычисляем разницу между нынешней даты и датой последнего создания скрипта Backup-YYYY-MM-DD
day_time=$(echo "(${currentDateSec} - ${lastBackupDateSec}) / 86400" | bc)

/// ВОТ ЭТО ПУНКТ с  В ЛАБЕ
// если разница меньше чем 7 дней и у нас дирекотрия с последнем резервным копированием не пуста, то
if [[ $day_time -lt 7 && "$lastBackupDir" != "" ]]
then
    // проходимся по файлам директории source и копирует все оттуда в
    for file in $(ls -1 "${SourceDir}")
    do
        if [[ -f "$BackupDir/Backup-$lastBackupDate/$file" ]]
        // Если файл с таким именем есть в source, то его размер сравнивается с размером одноименного файла
        // в действующем каталоге резервного копирования
        then
        //оператор позволяет вам выполнять вторую команду только в случае сбоя при выполнении первой команды,
        // то есть состояние выхода первой команды равно «1» — программа выполнена НЕ успешно
                cmp -s "$SourceDir/$file" "$BackupDir/Backup-$lastBackupDate/$file" ||
                {
                    // mv переименовывает старое_имя новое_имя
                    // старое_имя - это файл в backup в последнем каталоге
                    // новое_имя - это файл с нынешней датой
                    // здесь мы переименовываем уже имеющийся в backup файл
                    mv "$BackupDir/$lastBackupDir/$file"  "$BackupDir/$lastBackupDir/$file.$currentDate"
                    // здесь копируем файл из source в backup
                    cp -v "$SourceDir/$file" "$BackupDir/$lastBackupDir" >> $ReportFile
                }
        else
            // файла с таким именем в каталоге резервного копирования нет, то он копируется из /home/user/source
                cp -v "$SourceDir/$file" "$BackupDir/Backup-$lastBackupDate/$file" >> $ReportFile

        fi
    done


/// ВОТ ЭТО ПУНКТ b В ЛАБЕ
// Если новый каталог был создан, то скрипт скопирует в этот каталог все файлы из каталога
else
    // создаем новый каталог по формату Backup-YYYY-MM-D с нынешней датой
    dirPath="/home/$USER/Backup/Backup-${currentDate}"
    mkdir ${dirPath}

    // выводит нынешнюю дату и  имя нового каталога резервного копирования в файл в report
    echo "${currentDate} : backup directory ${dirPath}" >> $ReportFile

    // рекурсивное копирование директории Source с выводом подробной информации в Report
    // вот эта звездочка означает, что команда скопирует все файлы, начинающиеся на test: "$SourceDir/"
    /// TODO: сделать так, чтобы он не копировал вместе с каталогом source в новый созданный файл Backup-YYYY-MM-DD
    cp -rv "$SourceDir/"* "$dirPath" >> $ReportFile
        fi
