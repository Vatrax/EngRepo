using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace odtwarzacz_WPF
{
    public class Playlistelement
    {
        string _sourcedata;
        string _namedata;
        public Playlistelement(string source,string name) 
        {
            _sourcedata = source;
            _namedata = name;
        }
        public string sourcedata
        {
            get { return _sourcedata; }
            set { _sourcedata = value; }
        }
        public string namedata
        {
            get { return _namedata; }
            set { _namedata = value; }
        }
    }
}
