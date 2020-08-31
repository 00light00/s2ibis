TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=

HEADERS += \
    ConstantStuff.h \
    StreamGobbler.h \
    VIDataContainer.h \
    VITableList.h \
    Vds.h \
    VdsList.h \
    analyzeComponent.h \
    analyzePin.h \
    binParams.h \
    binTranData.h \
    cListContainer.h \
    callSpice.h \
    checkForAbort.h \
    checkForConvergence.h \
    completeDataStructures.h \
    componentList.h \
    create_VItable.h \
    diffPinList.h \
    findSupplyPins.h \
    generateRampData.h \
    generateVICurve.h \
    generateWaveData.h \
    getMatchingModel.h \
    getMatchingPin.h \
    getSpiceRampData.h \
    getSpiceVIData.h \
    getSpiceWaveData.h \
    goodies.h \
    ibisComponent.h \
    ibisDiffPin.h \
    ibisGlobal.h \
    ibisModel.h \
    ibisPackage.h \
    ibisPin.h \
    ibisPinMap.h \
    ibisRamp.h \
    ibisSeriesModel.h \
    ibisSeriesPin.h \
    ibisTOP.h \
    ibisTypMinMax.h \
    ibisVItable.h \
    ibisVItableEntry.h \
    ibisWaveTable.h \
    ibisWaveTableEntry.h \
    modelsList.h \
    pinMapList.h \
    pinsList.h \
    runSpiceAgain.h \
    s2iHeader.h \
    s2iParser.h \
    s2iReader.h \
    s2iString.h \
    s2ianalyz.h \
    s2ibis3.h \
    s2ibisPrint.h \
    s2ispice.h \
    s2iutil.h \
    seriesMosfet.h \
    seriesPinsList.h \
    seriesSwitchGpList.h \
    seriesSwitchGroup.h \
    setPinDC.h \
    setPinTran.h \
    setupDCSweepCommands.h \
    setupPwrAndTempCmds.h \
    setupSpiceFileNames.h \
    setupSpiceInputFile.h \
    setupTranCommands.h \
    setupVoltages.h \
    sortVIData.h \
    sortVISeriesData.h \
    spiceVT.h \
    waveTableList.h

