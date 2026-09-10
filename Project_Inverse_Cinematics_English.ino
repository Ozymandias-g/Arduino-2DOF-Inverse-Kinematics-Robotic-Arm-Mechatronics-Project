#include <Servo.h>
#include <math.h>

Servo omuz;
Servo dirsek;

// --- ROBOT DIMENSIONS ---
const float L1 = 18.0; // Shoulder length (cm)
const float L2 = 18.0; // Elbow length (cm)

// --- RADIAN TO DEGREE CONVERSION ---
const float RAD2DEG = 180.0 / PI;

void setup() {
  Serial.begin(9600);
  omuz.attach(9);
  dirsek.attach(10);
  
  Serial.println("--- INVERSE KINEMATICS ROBOTIC ARM ---");
  Serial.println("Enter coordinate: x,y (Ex: 36,0 or 0,36)");
  
  // Go to a safe starting position (Midpoint)
  // git(15, 15); 
}

void loop() {
  if (Serial.available() > 0) {
    float x = Serial.parseFloat();
    float y = Serial.parseFloat();
    
    if (Serial.read() == '\n') { // Wait for the end-of-line character
      git(x, y);
    }
  }
}

void git(float x, float y) {
  // 1. HYPOTENUSE CALCULATION (Bird's-eye distance to target)
  float r = sqrt(x*x + y*y);
  
  // SAFETY: If the target is further than the arm's length, limit it to avoid breaking the arm
  if (r > (L1 + L2)) {
    r = L1 + L2;
    Serial.println("WARNING: Out of range! Moving to the limit.");
  }

  // --- INVERSE KINEMATICS FORMULAS (Law of Cosines) ---
  
  // ELBOW ANGLE (Phi2) CALCULATION
  // Derived from the formula: c^2 = a^2 + b^2 - 2ab*cos(C)
  float cos_angle2 = (x*x + y*y - L1*L1 - L2*L2) / (2 * L1 * L2);
  
  // Mathematical error protection (Keep between -1.0 and 1.0)
  cos_angle2 = constrain(cos_angle2, -1.0, 1.0);
  
  float angle2_rad = acos(cos_angle2); // Elbow angle in radians
  
  // SHOULDER ANGLE (Theta1) CALCULATION
  // Accounts for both height (atan2) and elbow bending.
  float angle1_rad = atan2(y, x) - atan2((L2 * sin(angle2_rad)), (L1 + L2 * cos(angle2_rad)));

  // Convert Radians to Degrees
  float omuzAcisi = angle1_rad * RAD2DEG;
  float dirsekAcisi = angle2_rad * RAD2DEG;

  // --- SERVO MAPPING (THE MOST CRITICAL PART) ---
  // Converting mathematical angles to a language your servo motor understands.
  // YOU WILL CALIBRATE THE ROBOT BY ADJUSTING THESE NUMBERS.
  
  // SHOULDER: When math says 0 degrees (horizontal), what should your servo be? 
  // You wanted the shoulder to be 0 for (36,0). Usually servos are 0 or 90.
  int servoOmuz = omuzAcisi; 
  
  // ELBOW: When math says 0 degrees (arm completely straight), what should your servo be?
  // You wanted the elbow servo to stay at 90 at the point (36,0) (when the arm is straight).
  // Mathematically, the angle is 0 when the arm is straight. We add 90 to this.
  int servoDirsek = 90 + dirsekAcisi; // Or 90 - dirsekAcisi (Depends on direction)

  // Constrain degrees (To prevent servo damage)
  servoOmuz = constrain(servoOmuz, 0, 180);
  servoDirsek = constrain(servoDirsek, 0, 180);

  // Write to motors
  omuz.write(servoOmuz);
  dirsek.write(servoDirsek);
  
  // Provide info
  Serial.print("Moved to: "); Serial.print(x); Serial.print(","); Serial.println(y);
  Serial.print("Math Angles    -> Shoulder: "); Serial.print(omuzAcisi); Serial.print(" Elbow: "); Serial.println(dirsekAcisi);
  Serial.print("Servo Values   -> Shoulder: "); Serial.print(servoOmuz); Serial.print(" Elbow: "); Serial.println(servoDirsek);
  Serial.println("--------------------------------");
}