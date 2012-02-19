// This file is part of IRC Chatter, the first IRC Client for MeeGo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2011, Timur Kristóf <venemo@fedoraproject.org>
// Copyright (C) 2011, Hiemanshu Sharma <mail@theindiangeek.in>

#include <QtCore>

#include "serversettings.h"

ServerSettings::ServerSettings(QObject *parent, const QString &url, const quint16 &port, bool ssl, const QString &password, const QStringList &autoJoinChannels) :
    QObject(parent),
    _serverUrl(url),
    _serverPort(port),
    _serverSSL(ssl),
    _serverPassword(password),
    _autoJoinChannels(autoJoinChannels)
{
    if (!_autoJoinChannels.length() && url == "irc.freenode.net")
    {
        _autoJoinChannels.append("#irc-chatter");
        _autoJoinChannels.append("#harmattan");
    }
}

QString ServerSettings::autoJoinChannelsInPlainString() const
{
    return _autoJoinChannels.join(", ");
}

void ServerSettings::setAutoJoinChannelsInPlainString(const QString &value)
{
    _autoJoinChannels = value.split(",");
    for (int i = 0; i < _autoJoinChannels.count(); i++)
        _autoJoinChannels[i] = _autoJoinChannels[i].trimmed();
}

void ServerSettings::backendAsksForPassword(QString *password)
{
    *password = _serverPassword;
}

QDataStream &operator<<(QDataStream &stream, const ServerSettings &serverSettings)
{
    return stream
            << serverSettings.serverUrl()
            << serverSettings.serverPassword()
            << serverSettings.autoJoinChannels()
            << serverSettings.serverSSL()
            << serverSettings.serverPort()
            << serverSettings.userNickname()
            << serverSettings.userIdent()
            << serverSettings.userRealName()
            << serverSettings.shouldConnect();
}

QDataStream &operator>>(QDataStream &stream, ServerSettings &serverSettings)
{
    return stream
            >> serverSettings._serverUrl
            >> serverSettings._serverPassword
            >> serverSettings._autoJoinChannels
            >> serverSettings._serverSSL
            >> serverSettings._serverPort
            >> serverSettings._userNickname
            >> serverSettings._userIdent
            >> serverSettings._userRealName
            >> serverSettings._shouldConnect;
}
