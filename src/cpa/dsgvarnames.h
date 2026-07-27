#pragma once

#include <string_view>
#include <cstdint>

namespace R2MP::CPA::DsgVar {

    // Rayman DsgVar names
    enum class Rayman : uint32_t {
        POING_GrappinBis,
        HELICO_SuperHelico,
        HELICO_AccelerationVerticaleSuperHelico,
        HELICO_GraviteSuperHelico,
        HELICO_VitesseHorizontaleMax,
        HELICO_VitesseInterdictionHelicoGlisse,
        HELICO_PeutSauter,
        ANIM_vecAxeDeRotation,
        RAY_ReinitMode,
        RAY_Etat,
        RAY_PeutSeDeplacer,
        RAY_Rebond,
        RAY_RebondAutorise,
        RAY_Gravite,
        RAY_GraviteVariable,
        RAY_SautRelatif,
        RAY_ReagitAuxCommandes,
        RAY_TpsChuteMaxi,
        RAY_FightDistance,
        INTERN_PoingTempsAppuye,
        INTERN_PoingDemande,
        INTERN_SpeedZ,
        INTERN_RayVitesseInit,
        INTERN_SAUT_TempsAppuye,
        INTERN_BoucleSaut,
        INTERN_SAUT_CompteurEssaisAccrochage,
        INTERN_SAUT_VX,
        INTERN_SAUT_VY,
        INTERN_SAUT_VZ,
        INTERN_SAUT_TYPE,
        INTERN_SAUT_VY_LIMITE,
        INTERN_BloqueVitesse,
        INTERN_BloqueQuart,
        INTERN_BLOC_NullSpeed,
        INTERN_DateDernierContactAvecLeSol,
        INTERN_Tmp,
        INTERN_Tmp2,
        INTERN_TmpInt,
        INTERN_TmpVector,
        INTERN_TmpVector1,
        INTERN_TmpVector2,
        INTERN_TmpPerso,
        INTERN_mainDInit,
        INTERN_mainGInit,
        INTERN_EssaieAccrocher,
        INTERN_GiBloqueAvant,
        INTERN_HelicoPeutSauter,
        INTERN_NAGE_rVY,
        INTERN_NAGE_rRZ,
        INTERN_NAGE_rAltitudeSurface,
        INTERN_NAGE_bVeutAvancer,
        INTERN_NAGE_bVeutPlonger,
        INTERN_NAGE_bVeutTourner,
        INTERN_NAGE_vecAssiette,
        INTERN_NAGE_vecHorizon,
        INTERN_NAGE_vecVisee,
        INTERN_GRAPPIN_iRetournementEffectue,
        Force_DecrocheGrappin,
        INTERN_PersosRamassables,
        PersoGenerated,
        INTERN_PersoPlateForme,
        INTERN_EntreDeuxPossible,
        INTERN_EntreDeuxAxe,
        INTERN_EntreDeuxVecteurPos,
        INTERN_EntreDeuxMilieu,
        INTERN_EntreDeuxPos,
        INTERN_EntreDeuxProduitScalaire,
        INTERN_EntreDeuxAngleAvecAxe,
        INTERN_CollisionneurType,
        INTERN_PafVecteur,
        INTERN_VitessePere,
        INTERN_VitesseDeRotation,
        RAY_PafOriente,
        pad_force_inertie,
        PAD_Analog_Threshold,
        PAD_Analog_WaitToWalk,
        PAD_Analog_WalkToWait,
        Time4RayTransparent,
        RAY_RayIsHit,
        INTERN_RebondEnCours,
        INTERN_RattrappeLaPrune,
        NAGE_rVitesseTranslationMax,
        NAGE_HierarchieDeSurface,
        SAUT_TempsImpulsionMaximal,
        GI_RayLastVisee,
        RAY_PeutPasserEnNageDepuisMarche,
        INTERN_SautVitesseVersDescente,
        INTERN_RaySlideSpeed,
        INTERN_OrienteEnAttente,
        InternSautAChangeAnimDescente,
        INTERN_VientDeLHelico,
        INTERN_NageProfondeur,
        INTERN_EnGlisseRapide,
        INTERN_GenereFumee,
        INTERN_NewAssiete,
        InitialPositionIsRemembered,
        InitialTranslationInMap,
        InitialSightInMap,
        CoupeLePetitSaut,
        RAY_CanGrab,
        RAY_PeutFaireDelHelicoDepuisLaGlisse,
        RAY_MaxRunSpeed,
        RAY_ImpulsionSautAutomatique,
        RAY_InfluencePenteSurVitesse,
        RAY_InertiePadReduite,
        RAY_IgnoreLesPersosNonAffiches,
        RAY_SimplePaf,
        RAY_ShootTargetWeightX,
        RAY_ShootTargetWeightXY,
        RAY_ShootTargetWeightXYZ,
        INTERN_Tir_ActionAccumule,
        INTERN_Tir_ActionCanarde,
        INTERN_Tir_ActionRetourAttente,
        INTERN_Tir_PeutAccumuler,
        INTERN_Tir_AccumulationADonf,
        Count
    };

    // Global DsgVar names
    enum class Global : uint32_t {
        Codetexte,
        BulleTexte,
        Txtdelai,
        des_position_txt,
        Cages_NbrePastille,
        Cages_NbrePrises,
        CAGE_Machine_A_Sous,
        GLOBAL_Alarme,
        Nbr_Always,
        Hauteur,
        ModeLookVraimentInterdit,
        transparence_icone,
        MAX_Cheatcodes,
        CAM_ModeBanjoInterdit,
        CAM_ModeLookInterdit,
        No_Camera_Icon,
        CAM_Icon_Gone,
        t_camera,
        t_cameraLook,
        t_debut_map,
        Cine_Nego_10_Jouee,
        ChangeLangueDisponible,
        PadX,
        PadY,
        PosChar,
        CharNumber,
        SlotNumber,
        Acteur_RMbasket_actif,
        Acteur_RMbasket,
        Acteur_lums_sauvegarde_actif,
        RAY_Temps_Chrono,
        RAY_MillisecondesParPastille,
        RAY_LumGenerePos,
        Ray_LumType,
        Ray_Lum,
        Ray_LumPoing,
        Ray_LumPos,
        Ray_LumAngle,
        Ray_LumOffsetAltitude,
        Ray_LumRayon,
        Ray_LumAmplitude,
        INTERN_TmpVector,
        GLOBAL_Bits,
        LUMS_Compteur_Restant_Pastille,
        LUMS_Nombre_Total_Dans_Pastille,
        LUMS_Machine_A_Sous,
        CAGES_Nombre_Cassees,
        GLOBAL_SHOOT_SinusEffect,
        GLOBAL_SIEGERUSSE_DerniereAssiette,
        CapaBonus_Accumulation,
        CapaBonus_Grappin,
        LancementJeu,
        TmpTemps,
        CourseDemarre,
        Course_arrivee,
        sound_gone,
        t_dep_son,
        Scope,
        LTBX,
        TF1,
        Hauteur_Bandes,
        LUMS_Totaux_Pris,
        NBRE_LUMS_MAX,
        t_cheat,
        duree_cheat,
        cheat,
        Vec0,
        Vec1,
        Vec2,
        Count
    };

    // StdCam DsgVar names
    enum class StdCam : uint32_t {
        InterdireLook,
        InterdireBango,
        InterdireChgComport,
        ForcerCutLook,
        ForcerModeNormal,
        PasDeRefAxisMario,
        gencamera_priorite,
        InterdireCD,
        InterdireDoubleC,
        InterdireDoubleD,
        RequeteComportement,
        INTERN_TempVector,
        INTERN_TempVector1,
        INTERN_TempVector2,
        INTERN_VecteurZ,
        INTERN_VarappeMemo,
        INTERN_ReqVarappe,
        INTERN_TempsVarappe,
        INTERN_GrappinSpeedPP,
        INTERN_SaveAlpha,
        INTERN_SaveTheta,
        INTERN_StepAlpha,
        INTERN_StepTheta,
        INTERN_TStepAlpha,
        INTERN_TStepTheta,
        INTERN_MaxTheta,
        INTERN_MinTheta,
        INTERN_LastAddAlpha,
        INTERN_LastAddTheta,
        INTERN_Inertia,
        INTERN_DistMinLook,
        INTERN_ShiftPosLookZ,
        INTERN_RetourLook,
        INTERN_LookADestination,
        INTERN_Pere,
        INTERN_EnModeLook,
        INTERN_SortieLook,
        INTERN_ComportementActuel,
        INTERN_Mario_vector,
        INTERN_ConserveAxe,
        INTERN_VecteurCD,
        INTERN_SaveShiftTarget,
        INTERN_SortieCutLook,
        INTERN_PasDeGendoor,
        INTERN_ForceAxe,
        INTERN_TempReel,
        INTERN_DejaMontee,
        INTERN_SautZ,
        INTERN_SautZ1,
        INTERN_PeutMario,
        INTERN_A,
        INTERN_B,
        INTERN_TempReel1,
        INTERN_BloquerSaut,
        INTERN_PersoLook,
        INTERN_OkUneFois,
        INTERN_TempsJoy,
        INTERN_TempsRetour,
        INTERN_PeutRetour,
        INTERN_AddDist,
        INTERN_MemoPrune,
        INTERN_TempsPrune,
        INTERN_BloqueTarget,
        INTERN_PeutCD,
        INTERN_SurPrune,
        INTERN_MemoTgtPrune,
        INTERN_Hole,
        INTERN_BaseHole,
        INTERN_PeutCDStraf,
        INTERN_TempsLook,
        INTERN_TempsCD,
        INTERN_CDSens,
        INTERN_MemoViseePere,
        INTERN_DureeStraf,
        INTERN_TempsAutoFireStraf,
        INTERN_DureeModeBloque,
        INTERN_TempsAutoFireModeBloque,
        INTERN_SwitchMode,
        INTERN_ShiftTargetHelico,
        INTERN_TempsSaut,
        INTERN_DecalageTarget,
        INTERN_EnSaut,
        INTERN_Reel1,
        INTERN_TempsTarget,
        INTERN_NbTrames,
        INTERN_TempCoefTarget,
        INTERN_Coef,
        INTERN_Pente,
        INTERN_AnglePente,
        INTERN_FightTarget,
        INTERN_ShiftPosVarappe,
        INTERN_ShiftTargetVarappe,
        INTERN_NageDureeCol,
        INTERN_ShiftPosNage,
        INTERN_TempBool,
        INTERN_TempsCut,
        INTERN_EnCD,
        Count
    };

    constexpr std::string_view to_string(Rayman value) noexcept {
        switch (value) {
        case Rayman::POING_GrappinBis: return "DV_RAY_POING_GrappinBis";
        case Rayman::HELICO_SuperHelico: return "DV_RAY_HELICO_SuperHelico";
        case Rayman::HELICO_AccelerationVerticaleSuperHelico: return "DV_RAY_HELICO_AccelerationVerticaleSuperHelico";
        case Rayman::HELICO_GraviteSuperHelico: return "DV_RAY_HELICO_GraviteSuperHelico";
        case Rayman::HELICO_VitesseHorizontaleMax: return "DV_RAY_HELICO_VitesseHorizontaleMax";
        case Rayman::HELICO_VitesseInterdictionHelicoGlisse: return "DV_RAY_HELICO_VitesseInterdictionHelicoGlisse";
        case Rayman::HELICO_PeutSauter: return "DV_RAY_HELICO_PeutSauter";
        case Rayman::ANIM_vecAxeDeRotation: return "DV_RAY_ANIM_vecAxeDeRotation";
        case Rayman::RAY_ReinitMode: return "DV_RAY_RAY_ReinitMode";
        case Rayman::RAY_Etat: return "DV_RAY_RAY_Etat";
        case Rayman::RAY_PeutSeDeplacer: return "DV_RAY_RAY_PeutSeDeplacer";
        case Rayman::RAY_Rebond: return "DV_RAY_RAY_Rebond";
        case Rayman::RAY_RebondAutorise: return "DV_RAY_RAY_RebondAutorise";
        case Rayman::RAY_Gravite: return "DV_RAY_RAY_Gravite";
        case Rayman::RAY_GraviteVariable: return "DV_RAY_RAY_GraviteVariable";
        case Rayman::RAY_SautRelatif: return "DV_RAY_RAY_SautRelatif";
        case Rayman::RAY_ReagitAuxCommandes: return "DV_RAY_RAY_ReagitAuxCommandes";
        case Rayman::RAY_TpsChuteMaxi: return "DV_RAY_RAY_TpsChuteMaxi";
        case Rayman::RAY_FightDistance: return "DV_RAY_RAY_FightDistance";
        case Rayman::INTERN_PoingTempsAppuye: return "DV_RAY_INTERN_PoingTempsAppuye";
        case Rayman::INTERN_PoingDemande: return "DV_RAY_INTERN_PoingDemande";
        case Rayman::INTERN_SpeedZ: return "DV_RAY_INTERN_SpeedZ";
        case Rayman::INTERN_RayVitesseInit: return "DV_RAY_INTERN_RayVitesseInit";
        case Rayman::INTERN_SAUT_TempsAppuye: return "DV_RAY_INTERN_SAUT_TempsAppuye";
        case Rayman::INTERN_BoucleSaut: return "DV_RAY_INTERN_BoucleSaut";
        case Rayman::INTERN_SAUT_CompteurEssaisAccrochage: return "DV_RAY_INTERN_SAUT_CompteurEssaisAccrochage";
        case Rayman::INTERN_SAUT_VX: return "DV_RAY_INTERN_SAUT_VX";
        case Rayman::INTERN_SAUT_VY: return "DV_RAY_INTERN_SAUT_VY";
        case Rayman::INTERN_SAUT_VZ: return "DV_RAY_INTERN_SAUT_VZ";
        case Rayman::INTERN_SAUT_TYPE: return "DV_RAY_INTERN_SAUT_TYPE";
        case Rayman::INTERN_SAUT_VY_LIMITE: return "DV_RAY_INTERN_SAUT_VY_LIMITE";
        case Rayman::INTERN_BloqueVitesse: return "DV_RAY_INTERN_BloqueVitesse";
        case Rayman::INTERN_BloqueQuart: return "DV_RAY_INTERN_BloqueQuart";
        case Rayman::INTERN_BLOC_NullSpeed: return "DV_RAY_INTERN_BLOC_NullSpeed";
        case Rayman::INTERN_DateDernierContactAvecLeSol: return "DV_RAY_INTERN_DateDernierContactAvecLeSol";
        case Rayman::INTERN_Tmp: return "DV_RAY_INTERN_Tmp";
        case Rayman::INTERN_Tmp2: return "DV_RAY_INTERN_Tmp2";
        case Rayman::INTERN_TmpInt: return "DV_RAY_INTERN_TmpInt";
        case Rayman::INTERN_TmpVector: return "DV_RAY_INTERN_TmpVector";
        case Rayman::INTERN_TmpVector1: return "DV_RAY_INTERN_TmpVector1";
        case Rayman::INTERN_TmpVector2: return "DV_RAY_INTERN_TmpVector2";
        case Rayman::INTERN_TmpPerso: return "DV_RAY_INTERN_TmpPerso";
        case Rayman::INTERN_mainDInit: return "DV_RAY_INTERN_mainDInit";
        case Rayman::INTERN_mainGInit: return "DV_RAY_INTERN_mainGInit";
        case Rayman::INTERN_EssaieAccrocher: return "DV_RAY_INTERN_EssaieAccrocher";
        case Rayman::INTERN_GiBloqueAvant: return "DV_RAY_INTERN_GiBloqueAvant";
        case Rayman::INTERN_HelicoPeutSauter: return "DV_RAY_INTERN_HelicoPeutSauter";
        case Rayman::INTERN_NAGE_rVY: return "DV_RAY_INTERN_NAGE_rVY";
        case Rayman::INTERN_NAGE_rRZ: return "DV_RAY_INTERN_NAGE_rRZ";
        case Rayman::INTERN_NAGE_rAltitudeSurface: return "DV_RAY_INTERN_NAGE_rAltitudeSurface";
        case Rayman::INTERN_NAGE_bVeutAvancer: return "DV_RAY_INTERN_NAGE_bVeutAvancer";
        case Rayman::INTERN_NAGE_bVeutPlonger: return "DV_RAY_INTERN_NAGE_bVeutPlonger";
        case Rayman::INTERN_NAGE_bVeutTourner: return "DV_RAY_INTERN_NAGE_bVeutTourner";
        case Rayman::INTERN_NAGE_vecAssiette: return "DV_RAY_INTERN_NAGE_vecAssiette";
        case Rayman::INTERN_NAGE_vecHorizon: return "DV_RAY_INTERN_NAGE_vecHorizon";
        case Rayman::INTERN_NAGE_vecVisee: return "DV_RAY_INTERN_NAGE_vecVisee";
        case Rayman::INTERN_GRAPPIN_iRetournementEffectue: return "DV_RAY_INTERN_GRAPPIN_iRetournementEffectue";
        case Rayman::Force_DecrocheGrappin: return "DV_RAY_Force_DecrocheGrappin";
        case Rayman::INTERN_PersosRamassables: return "DV_RAY_INTERN_PersosRamassables";
        case Rayman::PersoGenerated: return "DV_RAY_PersoGenerated";
        case Rayman::INTERN_PersoPlateForme: return "DV_RAY_INTERN_PersoPlateForme";
        case Rayman::INTERN_EntreDeuxPossible: return "DV_RAY_INTERN_EntreDeuxPossible";
        case Rayman::INTERN_EntreDeuxAxe: return "DV_RAY_INTERN_EntreDeuxAxe";
        case Rayman::INTERN_EntreDeuxVecteurPos: return "DV_RAY_INTERN_EntreDeuxVecteurPos";
        case Rayman::INTERN_EntreDeuxMilieu: return "DV_RAY_INTERN_EntreDeuxMilieu";
        case Rayman::INTERN_EntreDeuxPos: return "DV_RAY_INTERN_EntreDeuxPos";
        case Rayman::INTERN_EntreDeuxProduitScalaire: return "DV_RAY_INTERN_EntreDeuxProduitScalaire";
        case Rayman::INTERN_EntreDeuxAngleAvecAxe: return "DV_RAY_INTERN_EntreDeuxAngleAvecAxe";
        case Rayman::INTERN_CollisionneurType: return "DV_RAY_INTERN_CollisionneurType";
        case Rayman::INTERN_PafVecteur: return "DV_RAY_INTERN_PafVecteur";
        case Rayman::INTERN_VitessePere: return "DV_RAY_INTERN_VitessePere";
        case Rayman::INTERN_VitesseDeRotation: return "DV_RAY_INTERN_VitesseDeRotation";
        case Rayman::RAY_PafOriente: return "DV_RAY_RAY_PafOriente";
        case Rayman::pad_force_inertie: return "DV_RAY_pad_force_inertie";
        case Rayman::PAD_Analog_Threshold: return "DV_RAY_PAD_Analog_Threshold";
        case Rayman::PAD_Analog_WaitToWalk: return "DV_RAY_PAD_Analog_WaitToWalk";
        case Rayman::PAD_Analog_WalkToWait: return "DV_RAY_PAD_Analog_WalkToWait";
        case Rayman::Time4RayTransparent: return "DV_RAY_Time4RayTransparent";
        case Rayman::RAY_RayIsHit: return "DV_RAY_RAY_RayIsHit";
        case Rayman::INTERN_RebondEnCours: return "DV_RAY_INTERN_RebondEnCours";
        case Rayman::INTERN_RattrappeLaPrune: return "DV_RAY_INTERN_RattrappeLaPrune";
        case Rayman::NAGE_rVitesseTranslationMax: return "DV_RAY_NAGE_rVitesseTranslationMax";
        case Rayman::NAGE_HierarchieDeSurface: return "DV_RAY_NAGE_HierarchieDeSurface";
        case Rayman::SAUT_TempsImpulsionMaximal: return "DV_RAY_SAUT_TempsImpulsionMaximal";
        case Rayman::GI_RayLastVisee: return "DV_RAY_GI_RayLastVisee";
        case Rayman::RAY_PeutPasserEnNageDepuisMarche: return "DV_RAY_RAY_PeutPasserEnNageDepuisMarche";
        case Rayman::INTERN_SautVitesseVersDescente: return "DV_RAY_INTERN_SautVitesseVersDescente";
        case Rayman::INTERN_RaySlideSpeed: return "DV_RAY_INTERN_RaySlideSpeed";
        case Rayman::INTERN_OrienteEnAttente: return "DV_RAY_INTERN_OrienteEnAttente";
        case Rayman::InternSautAChangeAnimDescente: return "DV_RAY_InternSautAChangeAnimDescente";
        case Rayman::INTERN_VientDeLHelico: return "DV_RAY_INTERN_VientDeLHelico";
        case Rayman::INTERN_NageProfondeur: return "DV_RAY_INTERN_NageProfondeur";
        case Rayman::INTERN_EnGlisseRapide: return "DV_RAY_INTERN_EnGlisseRapide";
        case Rayman::INTERN_GenereFumee: return "DV_RAY_INTERN_GenereFumee";
        case Rayman::INTERN_NewAssiete: return "DV_RAY_INTERN_NewAssiete";
        case Rayman::InitialPositionIsRemembered: return "DV_RAY_InitialPositionIsRemembered";
        case Rayman::InitialTranslationInMap: return "DV_RAY_InitialTranslationInMap";
        case Rayman::InitialSightInMap: return "DV_RAY_InitialSightInMap";
        case Rayman::CoupeLePetitSaut: return "DV_RAY_CoupeLePetitSaut";
        case Rayman::RAY_CanGrab: return "DV_RAY_RAY_CanGrab";
        case Rayman::RAY_PeutFaireDelHelicoDepuisLaGlisse: return "DV_RAY_RAY_PeutFaireDelHelicoDepuisLaGlisse";
        case Rayman::RAY_MaxRunSpeed: return "DV_RAY_RAY_MaxRunSpeed";
        case Rayman::RAY_ImpulsionSautAutomatique: return "DV_RAY_RAY_ImpulsionSautAutomatique";
        case Rayman::RAY_InfluencePenteSurVitesse: return "DV_RAY_RAY_InfluencePenteSurVitesse";
        case Rayman::RAY_InertiePadReduite: return "DV_RAY_RAY_InertiePadReduite";
        case Rayman::RAY_IgnoreLesPersosNonAffiches: return "DV_RAY_RAY_IgnoreLesPersosNonAffiches";
        case Rayman::RAY_SimplePaf: return "DV_RAY_RAY_SimplePaf";
        case Rayman::RAY_ShootTargetWeightX: return "DV_RAY_RAY_ShootTargetWeightX";
        case Rayman::RAY_ShootTargetWeightXY: return "DV_RAY_RAY_ShootTargetWeightXY";
        case Rayman::RAY_ShootTargetWeightXYZ: return "DV_RAY_RAY_ShootTargetWeightXYZ";
        case Rayman::INTERN_Tir_ActionAccumule: return "DV_RAY_INTERN_Tir_ActionAccumule";
        case Rayman::INTERN_Tir_ActionCanarde: return "DV_RAY_INTERN_Tir_ActionCanarde";
        case Rayman::INTERN_Tir_ActionRetourAttente: return "DV_RAY_INTERN_Tir_ActionRetourAttente";
        case Rayman::INTERN_Tir_PeutAccumuler: return "DV_RAY_INTERN_Tir_PeutAccumuler";
        case Rayman::INTERN_Tir_AccumulationADonf: return "DV_RAY_INTERN_Tir_AccumulationADonf";
        default: return "Unknown";
        }
    }

    constexpr std::string_view to_string(Global value) noexcept {
        switch (value) {
        case Global::Codetexte: return "DV_GLOBAL_Codetexte";
        case Global::BulleTexte: return "DV_GLOBAL_BulleTexte";
        case Global::Txtdelai: return "DV_GLOBAL_Txtdelai";
        case Global::des_position_txt: return "DV_GLOBAL_des_position_txt";
        case Global::Cages_NbrePastille: return "DV_GLOBAL_Cages_NbrePastille";
        case Global::Cages_NbrePrises: return "DV_GLOBAL_Cages_NbrePrises";
        case Global::CAGE_Machine_A_Sous: return "DV_GLOBAL_CAGE_Machine_A_Sous";
        case Global::GLOBAL_Alarme: return "DV_GLOBAL_GLOBAL_Alarme";
        case Global::Nbr_Always: return "DV_GLOBAL_Nbr_Always";
        case Global::Hauteur: return "DV_GLOBAL_Hauteur";
        case Global::ModeLookVraimentInterdit: return "DV_GLOBAL_ModeLookVraimentInterdit";
        case Global::transparence_icone: return "DV_GLOBAL_transparence_icone";
        case Global::MAX_Cheatcodes: return "DV_GLOBAL_MAX_Cheatcodes";
        case Global::CAM_ModeBanjoInterdit: return "DV_GLOBAL_CAM_ModeBanjoInterdit";
        case Global::CAM_ModeLookInterdit: return "DV_GLOBAL_CAM_ModeLookInterdit";
        case Global::No_Camera_Icon: return "DV_GLOBAL_No_Camera_Icon";
        case Global::CAM_Icon_Gone: return "DV_GLOBAL_CAM_Icon_Gone";
        case Global::t_camera: return "DV_GLOBAL_t_camera";
        case Global::t_cameraLook: return "DV_GLOBAL_t_cameraLook";
        case Global::t_debut_map: return "DV_GLOBAL_t_debut_map";
        case Global::Cine_Nego_10_Jouee: return "DV_GLOBAL_Cine_Nego_10_Jouee";
        case Global::ChangeLangueDisponible: return "DV_GLOBAL_ChangeLangueDisponible";
        case Global::PadX: return "DV_GLOBAL_PadX";
        case Global::PadY: return "DV_GLOBAL_PadY";
        case Global::PosChar: return "DV_GLOBAL_PosChar";
        case Global::CharNumber: return "DV_GLOBAL_CharNumber";
        case Global::SlotNumber: return "DV_GLOBAL_SlotNumber";
        case Global::Acteur_RMbasket_actif: return "DV_GLOBAL_Acteur_RMbasket_actif";
        case Global::Acteur_RMbasket: return "DV_GLOBAL_Acteur_RMbasket";
        case Global::Acteur_lums_sauvegarde_actif: return "DV_GLOBAL_Acteur_lums_sauvegarde_actif";
        case Global::RAY_Temps_Chrono: return "DV_GLOBAL_RAY_Temps_Chrono";
        case Global::RAY_MillisecondesParPastille: return "DV_GLOBAL_RAY_MillisecondesParPastille";
        case Global::RAY_LumGenerePos: return "DV_GLOBAL_RAY_LumGenerePos";
        case Global::Ray_LumType: return "DV_GLOBAL_Ray_LumType";
        case Global::Ray_Lum: return "DV_GLOBAL_Ray_Lum";
        case Global::Ray_LumPoing: return "DV_GLOBAL_Ray_LumPoing";
        case Global::Ray_LumPos: return "DV_GLOBAL_Ray_LumPos";
        case Global::Ray_LumAngle: return "DV_GLOBAL_Ray_LumAngle";
        case Global::Ray_LumOffsetAltitude: return "DV_GLOBAL_Ray_LumOffsetAltitude";
        case Global::Ray_LumRayon: return "DV_GLOBAL_Ray_LumRayon";
        case Global::Ray_LumAmplitude: return "DV_GLOBAL_Ray_LumAmplitude";
        case Global::INTERN_TmpVector: return "DV_GLOBAL_INTERN_TmpVector";
        case Global::GLOBAL_Bits: return "DV_GLOBAL_GLOBAL_Bits";
        case Global::LUMS_Compteur_Restant_Pastille: return "DV_GLOBAL_LUMS_Compteur_Restant_Pastille";
        case Global::LUMS_Nombre_Total_Dans_Pastille: return "DV_GLOBAL_LUMS_Nombre_Total_Dans_Pastille";
        case Global::LUMS_Machine_A_Sous: return "DV_GLOBAL_LUMS_Machine_A_Sous";
        case Global::CAGES_Nombre_Cassees: return "DV_GLOBAL_CAGES_Nombre_Cassees";
        case Global::GLOBAL_SHOOT_SinusEffect: return "DV_GLOBAL_GLOBAL_SHOOT_SinusEffect";
        case Global::GLOBAL_SIEGERUSSE_DerniereAssiette: return "DV_GLOBAL_GLOBAL_SIEGERUSSE_DerniereAssiette";
        case Global::CapaBonus_Accumulation: return "DV_GLOBAL_CapaBonus_Accumulation";
        case Global::CapaBonus_Grappin: return "DV_GLOBAL_CapaBonus_Grappin";
        case Global::LancementJeu: return "DV_GLOBAL_LancementJeu";
        case Global::TmpTemps: return "DV_GLOBAL_TmpTemps";
        case Global::CourseDemarre: return "DV_GLOBAL_CourseDemarre";
        case Global::Course_arrivee: return "DV_GLOBAL_Course_arrivee";
        case Global::sound_gone: return "DV_GLOBAL_sound_gone";
        case Global::t_dep_son: return "DV_GLOBAL_t_dep_son";
        case Global::Scope: return "DV_GLOBAL_Scope";
        case Global::LTBX: return "DV_GLOBAL_LTBX";
        case Global::TF1: return "DV_GLOBAL_TF1";
        case Global::Hauteur_Bandes: return "DV_GLOBAL_Hauteur_Bandes";
        case Global::LUMS_Totaux_Pris: return "DV_GLOBAL_LUMS_Totaux_Pris";
        case Global::NBRE_LUMS_MAX: return "DV_GLOBAL_NBRE_LUMS_MAX";
        case Global::t_cheat: return "DV_GLOBAL_t_cheat";
        case Global::duree_cheat: return "DV_GLOBAL_duree_cheat";
        case Global::cheat: return "DV_GLOBAL_cheat";
        case Global::Vec0: return "DV_GLOBAL_Vec0";
        case Global::Vec1: return "DV_GLOBAL_Vec1";
        case Global::Vec2: return "DV_GLOBAL_Vec2";
        default: return "Unknown";
        }
    }

    constexpr std::string_view to_string(StdCam value) noexcept {
        switch (value) {
        case StdCam::InterdireLook: return "DV_StdCam_InterdireLook";
        case StdCam::InterdireBango: return "DV_StdCam_InterdireBango";
        case StdCam::InterdireChgComport: return "DV_StdCam_InterdireChgComport";
        case StdCam::ForcerCutLook: return "DV_StdCam_ForcerCutLook";
        case StdCam::ForcerModeNormal: return "DV_StdCam_ForcerModeNormal";
        case StdCam::PasDeRefAxisMario: return "DV_StdCam_PasDeRefAxisMario";
        case StdCam::gencamera_priorite: return "DV_StdCam_gencamera_priorite";
        case StdCam::InterdireCD: return "DV_StdCam_InterdireCD";
        case StdCam::InterdireDoubleC: return "DV_StdCam_InterdireDoubleC";
        case StdCam::InterdireDoubleD: return "DV_StdCam_InterdireDoubleD";
        case StdCam::RequeteComportement: return "DV_StdCam_RequeteComportement";
        case StdCam::INTERN_TempVector: return "DV_StdCam_INTERN_TempVector";
        case StdCam::INTERN_TempVector1: return "DV_StdCam_INTERN_TempVector1";
        case StdCam::INTERN_TempVector2: return "DV_StdCam_INTERN_TempVector2";
        case StdCam::INTERN_VecteurZ: return "DV_StdCam_INTERN_VecteurZ";
        case StdCam::INTERN_VarappeMemo: return "DV_StdCam_INTERN_VarappeMemo";
        case StdCam::INTERN_ReqVarappe: return "DV_StdCam_INTERN_ReqVarappe";
        case StdCam::INTERN_TempsVarappe: return "DV_StdCam_INTERN_TempsVarappe";
        case StdCam::INTERN_GrappinSpeedPP: return "DV_StdCam_INTERN_GrappinSpeedPP";
        case StdCam::INTERN_SaveAlpha: return "DV_StdCam_INTERN_SaveAlpha";
        case StdCam::INTERN_SaveTheta: return "DV_StdCam_INTERN_SaveTheta";
        case StdCam::INTERN_StepAlpha: return "DV_StdCam_INTERN_StepAlpha";
        case StdCam::INTERN_StepTheta: return "DV_StdCam_INTERN_StepTheta";
        case StdCam::INTERN_TStepAlpha: return "DV_StdCam_INTERN_TStepAlpha";
        case StdCam::INTERN_TStepTheta: return "DV_StdCam_INTERN_TStepTheta";
        case StdCam::INTERN_MaxTheta: return "DV_StdCam_INTERN_MaxTheta";
        case StdCam::INTERN_MinTheta: return "DV_StdCam_INTERN_MinTheta";
        case StdCam::INTERN_LastAddAlpha: return "DV_StdCam_INTERN_LastAddAlpha";
        case StdCam::INTERN_LastAddTheta: return "DV_StdCam_INTERN_LastAddTheta";
        case StdCam::INTERN_Inertia: return "DV_StdCam_INTERN_Inertia";
        case StdCam::INTERN_DistMinLook: return "DV_StdCam_INTERN_DistMinLook";
        case StdCam::INTERN_ShiftPosLookZ: return "DV_StdCam_INTERN_ShiftPosLookZ";
        case StdCam::INTERN_RetourLook: return "DV_StdCam_INTERN_RetourLook";
        case StdCam::INTERN_LookADestination: return "DV_StdCam_INTERN_LookADestination";
        case StdCam::INTERN_Pere: return "DV_StdCam_INTERN_Pere";
        case StdCam::INTERN_EnModeLook: return "DV_StdCam_INTERN_EnModeLook";
        case StdCam::INTERN_SortieLook: return "DV_StdCam_INTERN_SortieLook";
        case StdCam::INTERN_ComportementActuel: return "DV_StdCam_INTERN_ComportementActuel";
        case StdCam::INTERN_Mario_vector: return "DV_StdCam_INTERN_Mario_vector";
        case StdCam::INTERN_ConserveAxe: return "DV_StdCam_INTERN_ConserveAxe";
        case StdCam::INTERN_VecteurCD: return "DV_StdCam_INTERN_VecteurCD";
        case StdCam::INTERN_SaveShiftTarget: return "DV_StdCam_INTERN_SaveShiftTarget";
        case StdCam::INTERN_SortieCutLook: return "DV_StdCam_INTERN_SortieCutLook";
        case StdCam::INTERN_PasDeGendoor: return "DV_StdCam_INTERN_PasDeGendoor";
        case StdCam::INTERN_ForceAxe: return "DV_StdCam_INTERN_ForceAxe";
        case StdCam::INTERN_TempReel: return "DV_StdCam_INTERN_TempReel";
        case StdCam::INTERN_DejaMontee: return "DV_StdCam_INTERN_DejaMontee";
        case StdCam::INTERN_SautZ: return "DV_StdCam_INTERN_SautZ";
        case StdCam::INTERN_SautZ1: return "DV_StdCam_INTERN_SautZ1";
        case StdCam::INTERN_PeutMario: return "DV_StdCam_INTERN_PeutMario";
        case StdCam::INTERN_A: return "DV_StdCam_INTERN_A";
        case StdCam::INTERN_B: return "DV_StdCam_INTERN_B";
        case StdCam::INTERN_TempReel1: return "DV_StdCam_INTERN_TempReel1";
        case StdCam::INTERN_BloquerSaut: return "DV_StdCam_INTERN_BloquerSaut";
        case StdCam::INTERN_PersoLook: return "DV_StdCam_INTERN_PersoLook";
        case StdCam::INTERN_OkUneFois: return "DV_StdCam_INTERN_OkUneFois";
        case StdCam::INTERN_TempsJoy: return "DV_StdCam_INTERN_TempsJoy";
        case StdCam::INTERN_TempsRetour: return "DV_StdCam_INTERN_TempsRetour";
        case StdCam::INTERN_PeutRetour: return "DV_StdCam_INTERN_PeutRetour";
        case StdCam::INTERN_AddDist: return "DV_StdCam_INTERN_AddDist";
        case StdCam::INTERN_MemoPrune: return "DV_StdCam_INTERN_MemoPrune";
        case StdCam::INTERN_TempsPrune: return "DV_StdCam_INTERN_TempsPrune";
        case StdCam::INTERN_BloqueTarget: return "DV_StdCam_INTERN_BloqueTarget";
        case StdCam::INTERN_PeutCD: return "DV_StdCam_INTERN_PeutCD";
        case StdCam::INTERN_SurPrune: return "DV_StdCam_INTERN_SurPrune";
        case StdCam::INTERN_MemoTgtPrune: return "DV_StdCam_INTERN_MemoTgtPrune";
        case StdCam::INTERN_Hole: return "DV_StdCam_INTERN_Hole";
        case StdCam::INTERN_BaseHole: return "DV_StdCam_INTERN_BaseHole";
        case StdCam::INTERN_PeutCDStraf: return "DV_StdCam_INTERN_PeutCDStraf";
        case StdCam::INTERN_TempsLook: return "DV_StdCam_INTERN_TempsLook";
        case StdCam::INTERN_TempsCD: return "DV_StdCam_INTERN_TempsCD";
        case StdCam::INTERN_CDSens: return "DV_StdCam_INTERN_CDSens";
        case StdCam::INTERN_MemoViseePere: return "DV_StdCam_INTERN_MemoViseePere";
        case StdCam::INTERN_DureeStraf: return "DV_StdCam_INTERN_DureeStraf";
        case StdCam::INTERN_TempsAutoFireStraf: return "DV_StdCam_INTERN_TempsAutoFireStraf";
        case StdCam::INTERN_DureeModeBloque: return "DV_StdCam_INTERN_DureeModeBloque";
        case StdCam::INTERN_TempsAutoFireModeBloque: return "DV_StdCam_INTERN_TempsAutoFireModeBloque";
        case StdCam::INTERN_SwitchMode: return "DV_StdCam_INTERN_SwitchMode";
        case StdCam::INTERN_ShiftTargetHelico: return "DV_StdCam_INTERN_ShiftTargetHelico";
        case StdCam::INTERN_TempsSaut: return "DV_StdCam_INTERN_TempsSaut";
        case StdCam::INTERN_DecalageTarget: return "DV_StdCam_INTERN_DecalageTarget";
        case StdCam::INTERN_EnSaut: return "DV_StdCam_INTERN_EnSaut";
        case StdCam::INTERN_Reel1: return "DV_StdCam_INTERN_Reel1";
        case StdCam::INTERN_TempsTarget: return "DV_StdCam_INTERN_TempsTarget";
        case StdCam::INTERN_NbTrames: return "DV_StdCam_INTERN_NbTrames";
        case StdCam::INTERN_TempCoefTarget: return "DV_StdCam_INTERN_TempCoefTarget";
        case StdCam::INTERN_Coef: return "DV_StdCam_INTERN_Coef";
        case StdCam::INTERN_Pente: return "DV_StdCam_INTERN_Pente";
        case StdCam::INTERN_AnglePente: return "DV_StdCam_INTERN_AnglePente";
        case StdCam::INTERN_FightTarget: return "DV_StdCam_INTERN_FightTarget";
        case StdCam::INTERN_ShiftPosVarappe: return "DV_StdCam_INTERN_ShiftPosVarappe";
        case StdCam::INTERN_ShiftTargetVarappe: return "DV_StdCam_INTERN_ShiftTargetVarappe";
        case StdCam::INTERN_NageDureeCol: return "DV_StdCam_INTERN_NageDureeCol";
        case StdCam::INTERN_ShiftPosNage: return "DV_StdCam_INTERN_ShiftPosNage";
        case StdCam::INTERN_TempBool: return "DV_StdCam_INTERN_TempBool";
        case StdCam::INTERN_TempsCut: return "DV_StdCam_INTERN_TempsCut";
        case StdCam::INTERN_EnCD: return "DV_StdCam_INTERN_EnCD";
        default: return "Unknown";
        }
    }

}