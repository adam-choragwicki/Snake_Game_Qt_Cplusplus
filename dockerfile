FROM adamchor/ubuntu-image-for-qt-gui

WORKDIR /app
COPY executable_linux ./executable_linux
CMD ["./executable_linux/Snake.sh"]

