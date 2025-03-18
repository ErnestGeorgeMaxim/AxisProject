using System.Windows;

namespace AxisProject.Models
{
    public class ClipboardManager
    {
        private static ClipboardManager _instance;
        private string _clipboardContent = string.Empty;
        private List<string> _clipboardHistory = new List<string>();
        private const int MaxHistoryItems = 10;
        private ClipboardManager() { }

        public static ClipboardManager Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new ClipboardManager();
                }
                return _instance;
            }
        }

        public void Copy(string text)
        {
            if (string.IsNullOrEmpty(text))
                return;

            _clipboardContent = text;
            AddToHistory(text);

            try
            {
                Clipboard.SetText(text);
            }
            catch (Exception)
            {
            }
        }

        public string Cut(string text)
        {
            Copy(text);
            return string.Empty;
        }

        public string Paste()
        {
            return _clipboardContent;
        }
        private void AddToHistory(string text)
        {
            if (_clipboardHistory.Count > 0 && _clipboardHistory[0] == text)
                return;
            _clipboardHistory.Insert(0, text);
            if (_clipboardHistory.Count > MaxHistoryItems)
            {
                _clipboardHistory.RemoveAt(_clipboardHistory.Count - 1);
            }
        }

        public List<string> GetHistory()
        {
            return _clipboardHistory;
        }
        public void ClearHistory()
        {
            _clipboardHistory.Clear();
        }
    }
}