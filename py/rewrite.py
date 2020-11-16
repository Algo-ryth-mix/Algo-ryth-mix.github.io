import re
from typing import Dict, List, Tuple

from rewrite_rules.rewrite_base import RewriteBase
from vprint import vprint1

class XToY(RewriteBase):

    rgx = re.compile('X')
    pattern = 'Y'

    def rewrite_source(self,source :str, meta : Dict[str,str]) -> List[Tuple[str, Dict[str,str]]]:
        vprint1("[XToY] Rewriter started")
        return [(self.rgx.sub(self.pattern,source), meta)]