
IOdictionary CouplingDict
(
    IOobject
    (
        "couplingDict",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

const dictionary TFMDict = CouplingDict.subDict("TFM");


//- make TFM class

bool useTFMGas = readBool(TFMDict.lookup("useTFMGas"));
bool useTFMSource = readBool(TFMDict.lookup("useTFMSource"));

vector gridOrigin;
TFMDict.lookup("gridOrigin") >> gridOrigin;
vector gridVertex;
TFMDict.lookup("gridVertex") >> gridVertex;
scalar gridSize = readScalar(TFMDict.lookup("gridSize"));

coarserGrid TFM
(
    mesh,
    gridOrigin,
    gridVertex,
    gridSize
);

