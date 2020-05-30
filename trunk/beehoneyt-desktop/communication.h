#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**
 * @file    communication.h
 * @brief   Déclaration de la classe Communication
 * @author  ACKERMANN Théo
 * @version 0.2
 */

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QDebug>

class Ihm;

/**
 * @class   Communication
 * @brief   Permet de recevoir les données
 * @author  ACKERMANN Théo
 * @version 0.2
 */

class Communication  : public QObject
{
    Q_OBJECT

public:
    Communication(QObject *parent = nullptr);
    ~Communication();

    void connecterTTN(QString hostname, int port, QString username, QString password);
    void souscrireTopic(QString topic);
    void desabonnerTopic(QString topic);

private:
    QMqttClient *client;
    QMqttSubscription *subscription;
    Ihm *ihm;                           //!< interface utilisateur

    QString extraireHorodatage(QJsonObject objetJSON);
    QString extraireDeviceID(QJsonObject objetJSON, QStringList listeCles, int position);
    double  extraireTemperatureInterieure(QJsonObject objetJSON);
    double  extraireTemperatureExterieure(QJsonObject objetJSON);
    double  extraireHumiditeInterieure(QJsonObject objetJSON);
    double  extraireHumiditeExterieure(QJsonObject objetJSON);
    int     extraireEnsoleillement(QJsonObject objetJSON);
    int     extrairePression(QJsonObject objetJSON);
    double  extrairePoids(QJsonObject objetJSON);
    int     extraireCharge(QJsonObject objetJSON);

    QString formaterHorodatage(QString horodatageBrut);

public slots:
    void decoderJson(const QByteArray &json);
    void changerEtatConnexion();

signals:
    void nouvelleValeurTemperatureInterieure(QString nomDeLaRuche, double temperatureInterieure, QString horodatage);
    void nouvelleValeurTemperatureExterieure(QString nomDeLaRuche, double temperatureExterieure, QString horodatage);
    void nouvelleValeurEnsoleillement(QString nomDeLaRuche, int ensoleillement, QString horodatage);
    void nouvelleValeurHumiditeInterieure(QString nomDeLaRuche, double humiditeInterieure, QString horodatage);
    void nouvelleValeurHumiditeExterieure(QString nomDeLaRuche, double humiditeExterieure, QString horodatage);
    void nouvelleValeurPression(QString nomDeLaRuche, int pression, QString horodatage);
    void nouvelleValeurPoids(QString nomDeLaRuche, double poids, QString horodatage);
    void nouvelleValeurCharge(QString nomDeLaRuche, int charge, QString horodatage);
    void nouvelEtatConnexion(int etat);
};

#endif // COMMUNICATION_H
