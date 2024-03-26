# $1 Server
# $2 Port
# $3 Nickname
# $4 Password

if [ ${1} == '*quacke*' ]; then
    SERVER_BOT="Q"
else
    SERVER_BOT="NickServ"
fi

echo "NICK ${3}" >> loginCommands.txt
echo "USER ${3} * * :${3}" >> loginCommands.txt
echo "privmsg ${SERVER_BOT} :IDENTIFY ${3} ${4}" >> loginCommands.txt

nc ${1} ${2} < loginCommands.txt
