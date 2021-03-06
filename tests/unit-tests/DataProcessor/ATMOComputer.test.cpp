//
//        ----[  QUALIT'AIR  ]----
//
//    Marsaud Menseau Thomasset Wallyn
//  Copyright © 2019 - All right reserved
//

#include "catch2/catch.hpp"


#include "../../../src/DataProcessor/include/ATMOComputer.h"

TEST_CASE("Testing ATMO", "[UT-DP-1]") {
    pointCollection atmoTest =
            {
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 130},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 190},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    },
                    {
                            {
                                    {
                                            {"SO2", 5},
                                            {"O3", 90},
                                            {"NO2", 50},
                                            {"PM10", 30}
                                    }
                            }
                    }

            };

    json out = R"({
            "atmo": 6
    })"_json;

    ATMOComputer agg(atmoTest);
    CHECK(agg.apply()->dump() == out.dump());

}