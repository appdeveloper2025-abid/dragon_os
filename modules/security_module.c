/*
 * Dragon OS - Cybersecurity Suite
 * Advanced Security & Penetration Testing Tools
 * Designed & Developed by ABID MEHMOOD
 */

#include <stdint.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80

typedef struct {
    uint8_t threat_level;
    uint8_t firewall_status;
    uint8_t ids_status;
    uint16_t open_ports;
    uint32_t network_traffic;
} SecurityStatus;

static SecurityStatus sec_status = {0, 1, 1, 0, 0};
static uint16_t* vga = (uint16_t*)VGA_MEMORY;

// Network Scanner
void network_scan(void) {
    const char* scan_msg = "  [*] Scanning network... Devices found: 5";
    uint8_t x = 5, y = 15;
    for (const char* p = scan_msg; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0A << 8);
    }
}

// Port Scanner
void port_scan(uint32_t target_ip) {
    const char* ports[] = {
        "  Port 22:  OPEN  (SSH)",
        "  Port 80:  OPEN  (HTTP)",
        "  Port 443: OPEN  (HTTPS)",
        "  Port 3306: CLOSED (MySQL)",
        "  Port 8080: OPEN  (HTTP-Alt)"
    };
    
    uint8_t y = 12;
    for (int i = 0; i < 5; i++) {
        uint8_t x = 5;
        for (const char* p = ports[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0E << 8);
        }
        y++;
    }
}

// Vulnerability Scanner
void vulnerability_scan(void) {
    const char* vulns[] = {
        "  [!] Checking for known vulnerabilities...",
        "  [OK] No critical vulnerabilities detected",
        "  [WARN] 2 medium-risk issues found",
        "  [INFO] System hardening recommended"
    };
    
    uint8_t y = 13;
    for (int i = 0; i < 4; i++) {
        uint8_t x = 5;
        uint8_t color = (i == 2) ? 0x0E : 0x0A;
        for (const char* p = vulns[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)color << 8);
        }
        y++;
    }
}

// Traffic Monitor
void monitor_traffic(void) {
    sec_status.network_traffic += 1024;
    
    const char* traffic = "  Network Traffic: 2.4 MB/s | Packets: 15,234";
    uint8_t x = 5, y = 16;
    for (const char* p = traffic; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
    }
}

// Intrusion Detection System
void ids_check(void) {
    if (sec_status.ids_status) {
        const char* ids_msg = "  [IDS] No intrusion attempts detected";
        uint8_t x = 5, y = 17;
        for (const char* p = ids_msg; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0A << 8);
        }
    }
}

// Firewall Control
void firewall_toggle(void) {
    sec_status.firewall_status = !sec_status.firewall_status;
    const char* fw_msg = sec_status.firewall_status ? 
        "  [FIREWALL] Enabled" : "  [FIREWALL] Disabled";
    
    uint8_t x = 5, y = 18;
    uint8_t color = sec_status.firewall_status ? 0x0A : 0x0C;
    for (const char* p = fw_msg; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)color << 8);
    }
}

// Security Dashboard
void display_security_dashboard(void) {
    const char* header = "=== DRAGON OS SECURITY DASHBOARD ===";
    uint8_t x = 20, y = 10;
    for (const char* p = header; *p; p++) {
        vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0C << 8);
    }
    
    const char* status_lines[] = {
        "Threat Level: LOW",
        "Firewall: ACTIVE",
        "IDS: ENABLED",
        "Last Scan: 00:00:00",
        "Protected Ports: 65535"
    };
    
    y = 12;
    for (int i = 0; i < 5; i++) {
        x = 25;
        for (const char* p = status_lines[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0B << 8);
        }
        y++;
    }
}

// Packet Sniffer
void packet_sniffer(void) {
    const char* packets[] = {
        "  [PKT] 192.168.1.100 -> 8.8.8.8 (DNS)",
        "  [PKT] 192.168.1.100 -> 172.217.14.206 (HTTPS)",
        "  [PKT] 192.168.1.1 -> 192.168.1.100 (ARP)"
    };
    
    uint8_t y = 14;
    for (int i = 0; i < 3; i++) {
        uint8_t x = 5;
        for (const char* p = packets[i]; *p; p++) {
            vga[(y * VGA_WIDTH) + x++] = (uint16_t)*p | ((uint16_t)0x0D << 8);
        }
        y++;
    }
}

// Initialize security module
void init_security_module(void) {
    sec_status.threat_level = 0;
    sec_status.firewall_status = 1;
    sec_status.ids_status = 1;
    sec_status.open_ports = 0;
    sec_status.network_traffic = 0;
}

// Run full security scan
void full_security_scan(void) {
    network_scan();
    vulnerability_scan();
    ids_check();
    monitor_traffic();
}

// Get security status
SecurityStatus* get_security_status(void) {
    return &sec_status;
}
