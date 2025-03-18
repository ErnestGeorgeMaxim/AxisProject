using System.IO;
using System.Xml.Serialization;

namespace AxisProject.Models
{
    public class SettingsManager
    {
        private static SettingsManager _instance;
        private readonly string _settingsFilePath;
        private CalculatorSettings _settings;

        private SettingsManager()
        {
            try
            {
                // Try to use the application's directory instead
                string appDirectory = AppDomain.CurrentDomain.BaseDirectory;
                _settingsFilePath = Path.Combine(appDirectory, "calculatorSettings.xml");

                Console.WriteLine($"Settings file path: {_settingsFilePath}");

                LoadSettings();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error in SettingsManager constructor: {ex.Message}");
                // Create default settings if we can't even set up the file path
                _settings = new CalculatorSettings
                {
                    IsDigitGroupingEnabled = false,
                    CalculatorMode = CalculatorMode.Standard,
                    NumberSystem = NumberSystem.DEC
                };
            }
        }

        public static SettingsManager Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new SettingsManager();
                }
                return _instance;
            }
        }

        public bool IsDigitGroupingEnabled
        {
            get => _settings.IsDigitGroupingEnabled;
            set
            {
                _settings.IsDigitGroupingEnabled = value;
                SaveSettings();
            }
        }

        public CalculatorMode CalculatorMode
        {
            get => _settings.CalculatorMode;
            set
            {
                _settings.CalculatorMode = value;
                SaveSettings();
            }
        }

        public NumberSystem NumberSystem
        {
            get => _settings.NumberSystem;
            set
            {
                _settings.NumberSystem = value;
                SaveSettings();
            }
        }

        private void LoadSettings()
        {
            try
            {
                if (File.Exists(_settingsFilePath))
                {
                    using (var stream = new FileStream(_settingsFilePath, FileMode.Open))
                    {
                        var serializer = new XmlSerializer(typeof(CalculatorSettings));
                        _settings = (CalculatorSettings)serializer.Deserialize(stream);
                    }
                }
                else
                {
                    _settings = new CalculatorSettings
                    {
                        IsDigitGroupingEnabled = false,
                        CalculatorMode = CalculatorMode.Standard,
                        NumberSystem = NumberSystem.DEC
                    };
                    SaveSettings();
                }
            }
            catch (Exception ex)
            {
                _settings = new CalculatorSettings
                {
                    IsDigitGroupingEnabled = false,
                    CalculatorMode = CalculatorMode.Standard,
                    NumberSystem = NumberSystem.DEC
                };
                Console.WriteLine($"Error loading settings: {ex.Message}");
            }
        }

        private void SaveSettings()
        {
            try
            {
                using (var stream = new FileStream(_settingsFilePath, FileMode.Create))
                {
                    var serializer = new XmlSerializer(typeof(CalculatorSettings));
                    serializer.Serialize(stream, _settings);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error saving settings: {ex.Message}");
            }
        }
    }

    public enum CalculatorMode
    {
        Standard,
        Programmer
    }

    [Serializable]
    public class CalculatorSettings
    {
        public bool IsDigitGroupingEnabled { get; set; }
        public CalculatorMode CalculatorMode { get; set; }
        public NumberSystem NumberSystem { get; set; }
    }
}
