if [ ! -d "executable_linux" ]; then
    wget https://github.com/adam-choragwicki/Snake_Game_Qt_Cplusplus/releases/latest/download/executable_linux.zip
    unzip executable_linux.zip && rm executable_linux.zip
    chmod +x executable_linux/Snake.sh executable_linux/Snake
fi

./executable_linux/Snake
