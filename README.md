# CPP Work

CPP Work contains some funny tools for image comparation, snowflake connection and json parse tools for CPP.

## How to run it?

Download the code to local,

```shell
git clone git@git.appannie.org:fzhu/cppwork.git
```

Create a docker container on your local machine,
```shell
cd cppwork

docker run --name fedora-cpp --privileged -d -ti -v .:/cppwork registry.appannie.org/appannie/aa-docker-test/fedora-cpp:v1.1.1  bash
```

Go into the docker, 
```shell
docker exec -ti fedora-cpp bash
```

Then make the target project, and run the test for it

```shell
# images_timeline for an example

cd /cppwork/include/images_timeline/test/build

rm -fr *

cmake ..

make 

./images_test --gtest_filter="*Icon*"
```

## Support
Any problem pls feel free to contact fzhu@appannie.com.

