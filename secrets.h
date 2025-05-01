#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32-thing"

const char WIFI_SSID[] = "[WIFINAME]";
const char WIFI_PASSWORD[] = "[WIFIPASS]";
const char AWS_IOT_ENDPOINT[] = "[ENDPOINT]";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
//[KEY]
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
//[KEY]
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
//[KEY]
-----END RSA PRIVATE KEY-----
)KEY";
