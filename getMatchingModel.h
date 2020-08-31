#ifndef _GETMATCHINGMODEL
#define _GETMATCHINGMODEL

class getMatchingModel
{
  public ibisModel getMatchingModel(String searchName, modelsList modelList) {
    modelList.gototop();
    ibisModel tempModel = new ibisModel();
    tempModel = modelList.current;

    if (searchName.equalsIgnoreCase("")) {
      return null;
    }
    while (tempModel != null && !searchName.equalsIgnoreCase(tempModel.modelName)) {

      tempModel = modelList.current;
      modelList.next();
    }

    if (tempModel == null)
    {
      System.out.println("Model " + searchName + " Not Found in model list");
    }
    return tempModel;
  }
}

#endif
