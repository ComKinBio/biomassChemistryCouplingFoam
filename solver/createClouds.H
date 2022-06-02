Info<< "\nConstructing coal cloud" << endl;
biomassCloud bioCloud
(
    "bioCloud",
    rhoc,
    Uc,
    g,
    slgThermo,
    Ucavg,
    rhoavg,
    muavg,
    alphacavg,
    Tavg,
    kappaavg,
    Cpavg
);
