xhost +local:docker

if [[ "$(docker images -q snake 2> /dev/null)" == "" ]]; then
  docker build -t snake .
fi

docker run -d --rm --env="DISPLAY" --net=host snake

