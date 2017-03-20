## Surface Remesh

## Description

Surface reconstruction from rotated spheres (after RigidAlignment) or from coefficients (after GROUPS).


## Build

#### Requirements 

Building SurfRemesh requires to have built previously:

* MeshLib (https://github.com/pdedumast/MeshLib)
* SlicerExecutionModel

SurfRemesh can either be built from GROUPS SuperBuild.


###### Linux or MacOSX 

Consider this tree of repertories:
```
~/Project/SurfRemesh
         /SurfRemesh-build
```

Start a terminal.
First change your current working directory to the build directory ```SurfRemesh-build```
```
cd ~/Project/SurfRemesh-build
```

Generate the project using ```cmake```
```
cmake -DMeshLib_DIR:PATH=path/to/MeshLib -DSlicerExecutionModel:PATH=path/to/SlicerExecutionModel ../SurfRemesh
make
```


## Usage

Reconstruction from new rotated sphere, after RigidAlignment:
Output surface will have the same parametrization with one specified by the reference sphere.
```
./SurfRemesh --input [<std::string> input surface model] --tempModel [<std::string> rotate sphere] 
--ref [<std::string> common sphere model (same as refSphere in RigidAlignment)] 
--output [<std::string> reconstructed surface]
```

Reconstruction from coefficients, after GROUPS:
```
./SurfRemesh --input [<std::string> input surface model] --tempModel [<std::string> sphere model used in GROUPS] 
--ref [<std::string> common sphere model] --coeff [<std::string> Coefficients file from GROUPS]
--output [<std::string> reconstructed surface]
```

## Licence

See LICENSE.txt for information on using and contributing.