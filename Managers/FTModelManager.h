

class FTModelManager
{
public:
                            FTModelManager();
                            ~FTModelManager();
    
    FTModelFactory*         m_pModelFactory;
    FTModelTreeManager*     m_pModelTreeManager;
    FTGroup*                m_pRootGroup;
};

