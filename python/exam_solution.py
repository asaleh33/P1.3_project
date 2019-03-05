from datetime import datetime 

class PostcardList:
    def __init__(self):
        self._file = None
        self._postcards =[]
        self._date = {}
        self._from = {}
        self._to = {}

    def writeFile(self, _file):
        with open(self._file, 'w') as f:
            for ele in self._postcards:
                f.write("%s\n" % ele)
    
    def readFile(self,_file):
        self.updateLists(_file)

    def parsePostcards(self, _postcardlines):
        sep = _postcardlines.strip().split()
        _date = sep[0].split(":")[1][:-1]
        _from = sep[1].split(":")[1][:-1]
        _to = sep[2].split(":")[1][:-1]
        return _date, _from, _to

    def updateFile(self, _file):
        with open(self._file, 'a') as f:
            for ele in self._postcards:
                f.write("%s\n" % ele)
    
    def updateLists(self, _file):
        self._file = _file
        with open(self._file, 'r') as f:
            for line in f:
                sep = line.strip()
                len_list = self.getNumberOfPostcards()
                self._postcards.append(line)
                _date, _from, _to = self.parsePostcards(line)
                if not _date in self._date:
                    self._date[_date] = list()
                self._date[_date].append(len_list)
                if not  _from in self._from:
                    self._from[_from] = list()
                self._from[_from].append(len_list)
                if not  _to in self._to:
                    self._to[_to] = list()
                self._to[_to].append(len_list)

    def getNumberOfPostcards(self):
        return len(self._postcards)

    def getPostcardsByDateRange(self,date_range):
        postcards_date_range = []
        #postcard_range = []
        for date in self._date.keys():
            if date_range[0] <= datetime.strptime(date, "%Y-%m-%d") <= date_range[-1]:
                postcards_date_range +=[self._postcards[x] for x in self._date[date]]
                #postcards_date_range += self._date[date]
                #postcard_range =[self._postcards[x] for x in postcards_date_range]
        #return postcard_range
        return postcards_date_range

    def getPostcardsBySender(self, sender):
        postcards_from_sender = []
        if sender in self._from.keys():
            postcards_from_sender = [self._postcards[i] for i in self._from[sender]]
        return postcards_from_sender

    def getPostcardsByReceiver(self, receiver):
        postcards_to_receiver=[]
        if receiver in self._to:
            postcards_to_receiver = [self._postcards[i] for i in self._to[receiver]]   	
        return postcards_to_receiver

if __name__ == '__main__':
    __all__=['PostcardList']

