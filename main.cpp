#include "lofi.h"
#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QCommandLineParser>
#include <sys/stat.h>

// inline bool does (const std::string& name) {
//   struct stat buffer;
//   return (stat (name.c_str(), &buffer) == 0);
// }

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    lofi window;

    QApplication::setApplicationVersion("1.1");
    QCoreApplication::setApplicationName("Lofi Player");

    // Allow for the use of a custom stream file, if provided via commandline argument
    QCommandLineParser parser;
    parser.setApplicationDescription("Lofi Player");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption streamOption(QStringList() << "s"
                                                  << "streams",
                                    QCoreApplication::translate("main", "JSON file to read streams from. A list of dictionaries with 'name' and 'url' fields."),
                                    QCoreApplication::translate("main", "stream_file"));
    parser.addOption(streamOption);
    parser.process(app);
    if (parser.isSet(streamOption))
    {
        std::string newFileLocation = parser.value(streamOption).toStdString();
        window.jsonStreamFileLocationCustom = newFileLocation;
    }

    // Check if stream file exists, and load them. If it doesn't exist, quit out
    // Perform check here as the default file may not exist as well
    if (!window.setStreams())
    {
        QString message = QString("Stream file location provided either doesn't exist or can't be accessed. File given:\n") \
            + QString::fromStdString(window.getJsonStreamsFileLocation());

        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.finished(1);
        return msgBox.exec();
    }

    window.show();
    return app.exec();
}
