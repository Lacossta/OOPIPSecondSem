import java.io.FileWriter;
import java.io.IOException;

public class Main {

    // Константы для радиусов Земли и Солнца
    private static final double EARTH_RADIUS_MILES = 7926.0 / 2; // Радиус Земли в милях
    private static final double EARTH_RADIUS_KM = 12756.0 / 2;  // Радиус Земли в километрах
    private static final double SUN_RADIUS_MILES = 864000.0 / 2; // Радиус Солнца в милях
    private static final double SUN_RADIUS_KM = 1391980.0 / 2;  // Радиус Солнца в километрах

    public static void main(String[] args) {
        // Вычисляем объем Земли и Солнца в кубических милях и километрах
        double earthVolumeMiles = calculateVolume(EARTH_RADIUS_MILES);
        double earthVolumeKm = calculateVolume(EARTH_RADIUS_KM);
        double sunVolumeMiles = calculateVolume(SUN_RADIUS_MILES);
        double sunVolumeKm = calculateVolume(SUN_RADIUS_KM);

        // Вычисляем отношение объема Солнца к объему Земли
        double volumeRatio = sunVolumeMiles / earthVolumeMiles;

        // Выводим результаты на экран
        System.out.println("Объем Земли:");
        System.out.println("В кубических милях: " + earthVolumeMiles);
        System.out.println("В кубических километрах: " + earthVolumeKm);

        System.out.println("\nОбъем Солнца:");
        System.out.println("В кубических милях: " + sunVolumeMiles);
        System.out.println("В кубических километрах: " + sunVolumeKm);

        System.out.println("\nОтношение объема Солнца к объему Земли: " + volumeRatio);

        // Записываем результаты в файл
        try (FileWriter writer = new FileWriter("volume_results.txt")) {
            writer.write("Объем Земли:\n");
            writer.write("В кубических милях: " + earthVolumeMiles + "\n");
            writer.write("В кубических километрах: " + earthVolumeKm + "\n");

            writer.write("\nОбъем Солнца:\n");
            writer.write("В кубических милях: " + sunVolumeMiles + "\n");
            writer.write("В кубических километрах: " + sunVolumeKm + "\n");

            writer.write("\nОтношение объема Солнца к объему Земли: " + volumeRatio + "\n");
        } catch (IOException e) {
            System.out.println("Ошибка записи в файл: " + e.getMessage());
        }
    }

    // Метод для вычисления объема шара по формуле 4/3 * π * r^3
    public static double calculateVolume(double radius) {
        return (4.0 / 3.0) * Math.PI * Math.pow(radius, 3);
    }
}
