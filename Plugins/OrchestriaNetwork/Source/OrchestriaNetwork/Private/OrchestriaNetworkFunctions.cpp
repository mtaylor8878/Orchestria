#include "OrchestriaNetworkPrivatePCH.h"

#if PLATFORM_ANDROID

#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"

#define INIT_JAVA_METHOD(name, signature) \
if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
	name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
	check(name != NULL); \
} else { \
	check(0); \
}

#define DECLARE_JAVA_METHOD(name) \
static jmethodID name = NULL;

// Here goes the name of the method in the Java side
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartAdvertising);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartDiscovery);	
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetConnectionList);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_SetPlayerName);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestConnection);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestConnectionStatus);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_Disconnect);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_UpdateClients);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestRole);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_SetHostRole);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetRoles);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartGame);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ReportReady);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetGameState);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetStartDelay);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetScore);
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ReportScore);

void UOrchestriaNetworkFunctions::InitJavaFunctions()
{
	// Same here, but we add the Java signature (the type of the parameters is between the parameters, and the return type is added at the end,
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartAdvertising, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartDiscovery, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetConnectionList, "([Ljava/lang/String;)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_SetPlayerName, "(Ljava/lang/String;)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestConnection, "(Ljava/lang/String;)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestConnectionStatus, "([I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_Disconnect, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_UpdateClients, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_RequestRole, "(I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_SetHostRole, "(I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetRoles, "([I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_StartGame, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ReportReady, "()V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetGameState, "([I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetStartDelay, "([F)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetScore, "([I)V");
    INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ReportScore, "(I)V");
}
#undef DECLARE_JAVA_METHOD
#undef INIT_JAVA_METHOD

#endif

void UOrchestriaNetworkFunctions::OrchestriaNetwork_StartAdvertising() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_StartAdvertising);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_StartDiscovery() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_StartDiscovery);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

TArray<FString> UOrchestriaNetworkFunctions::OrchestriaNetwork_GetConnectionInfo() {
    TArray<FString> connections;
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jclass stringClass = Env->FindClass("java/lang/String");
        if (stringClass == NULL) {
            UE_LOG(LogAndroid, Error, TEXT("String class not found"));
            return connections;
        }

        jobjectArray result = Env->NewObjectArray(8, stringClass, NULL);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetConnectionList, result);

        for (int i = 0; i < 8; i++) {
            jstring string = (jstring) (Env->GetObjectArrayElement(result, i));
            const char *rawString = Env->GetStringUTFChars(string, 0);

            connections.Emplace(rawString);

            Env->ReleaseStringUTFChars(string, rawString);
            Env->DeleteLocalRef(string);
        }

        Env->DeleteLocalRef(result);
        Env->DeleteLocalRef(stringClass);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
    return connections;
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_SetPlayerName(const FString& name) {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jstring string = Env->NewStringUTF(TCHAR_TO_UTF8(*name));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_SetPlayerName, string);

        Env->DeleteLocalRef(string);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_RequestConnection(const FString& endpointId) {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jstring string = Env->NewStringUTF(TCHAR_TO_UTF8(*endpointId));
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_RequestConnection, string);

        Env->DeleteLocalRef(string);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

int UOrchestriaNetworkFunctions::OrchestriaNetwork_RequestConnectionStatus() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jintArray result = Env->NewIntArray(1);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_RequestConnectionStatus, result);

        jint* resultArr = Env->GetIntArrayElements(result, 0);

        const int resultInt = resultArr[0];

        Env->DeleteLocalRef(result);

        return resultInt;
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
        return 0;
    }
#endif
    return 0;
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_Disconnect() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_Disconnect);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_UpdateClients() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_UpdateClients);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_RequestRole(int roleId) {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_RequestRole, roleId);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_SetHostRole(int roleId) {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_SetHostRole, roleId);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

TArray<int> UOrchestriaNetworkFunctions::OrchestriaNetwork_GetRoles() {
    TArray<int> roles;
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jintArray intArray = Env->NewIntArray(4);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetRoles, intArray);

        jint* resultArr = Env->GetIntArrayElements(intArray, 0);

        roles.Add(resultArr[3]);
        for (int i = 0; i < 3; i++) {
            roles.Add(resultArr[i]);
        }

        Env->DeleteLocalRef(intArray);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
    return roles;
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_StartGame() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_StartGame);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_ReportReady() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_ReportReady);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}

int UOrchestriaNetworkFunctions::OrchestriaNetwork_GetGameState() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jintArray result = Env->NewIntArray(1);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetGameState, result);

        jint* resultArr = Env->GetIntArrayElements(result, 0);

        const int resultInt = resultArr[0];

        Env->DeleteLocalRef(result);

        return resultInt;
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
    return 0;
}

float UOrchestriaNetworkFunctions::OrchestriaNetwork_GetStartDelay() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jfloatArray result = Env->NewFloatArray(1);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetStartDelay, result);

        jfloat* resultArr = Env->GetFloatArrayElements(result, 0);

        const float resultFloat = resultArr[0];

        Env->DeleteLocalRef(result);

        return resultFloat;
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));

        return 0;
    }
#endif
    return 0.0f;
}

int UOrchestriaNetworkFunctions::OrchestriaNetwork_GetScore() {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jintArray result = Env->NewIntArray(1);
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetScore, result);

        jint* resultArr = Env->GetIntArrayElements(result, 0);

        const int resultInt = resultArr[0];

        Env->DeleteLocalRef(result);

        return resultInt;
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));

        return 0;
    }
#endif
    return 0;
}

void UOrchestriaNetworkFunctions::OrchestriaNetwork_ReportScore(int value) {
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_ReportScore, value);
    }
    else {
        UE_LOG(LogAndroid, Error, TEXT("Could not get Java ENV"));
    }
#endif
}
