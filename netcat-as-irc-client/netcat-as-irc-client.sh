# $1 Server
# $2 Port
# $3 Nickname
# $4 Password

BOT_NAME="NickServ" # Most common / Default one

if [ $1 == "*quake*" ]; then
    BOT_NAME="Q"
fi

main() {
    starting

    connect

    login

    pong
}

starting() {
    echo
    echo "Connecting to: ${1}:${2}"
    echo "Nickname: ${3}"
    echo "Password: ${4}"
    echo
}

connect() {
}

login() {
    echo "NICK ${3}"
    echo "USER ${3} * * :${3}"
    echo "privmsg ${BOT_NAME} :IDENTIFY ${3} ${4}"
}

pong() {
    
}
