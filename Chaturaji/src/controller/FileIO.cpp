//
// Created by houwe on 11/10/2024.
//

#include "FileIO.h"

#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>


FileIO::FileIO(const QString &mFilePath) : m_filePath(mFilePath), m_file(mFilePath) {}

int FileIO::saveBoard() {
    //TODO: TEMPERRARY TEST CODE
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << m_file.errorString();
        return EXIT_FAILURE;
    }

    QTextStream out(&m_file);
    out << "Hello, World!" << Qt::endl;

    // Close the file
    m_file.close();

    qDebug() << "File written successfully.";
    return 0; // Exit successfully
}