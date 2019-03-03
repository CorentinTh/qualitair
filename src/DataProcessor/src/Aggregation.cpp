//
// Created by Wallyn Valentin on 17/02/2019.
//

#include "../include/Aggregation.h"

std::unordered_map<std::string, double> Aggregation::computeAverage() {
    std::unordered_map<std::string, double> sums;
    std::unordered_map<std::string, int> count;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    sums[it->first] += it->second;
                    count[it->first]++;

                }
            }
        }
    }

    //transform sums to mean
    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        //round to 2 digits
        sums[it->first] = std::floor((sums[it->first] / count[it->first]) * 100.0 + 0.5) / 100.0;
    }

    return sums;
}

std::unordered_map<std::string, std::pair<double, double>> Aggregation::computeExtrems() {
    std::unordered_map<std::string, std::pair<double, double>> results;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    //initial values
                    if (!results.count(it->first))
                    {
                        results[it->first] = std::pair<double, double>(it->second, it->second);
                    }
                    //min
                    if (it->second < results[it->first].first) {
                        results[it->first].first = it->second;
                    }
                    //max
                    if (it->second > results[it->first].second) {
                        results[it->first].second = it->second;
                    }
                }
            }
        }
    }

    return results;
}

std::unordered_map<std::string, double> Aggregation::computeDeviation() {
    std::unordered_map<std::string, double> sums;
    std::unordered_map<std::string, double> deviations;
    std::unordered_map<std::string, int> count;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    sums[it->first] += it->second;
                    count[it->first]++;

                }
            }
        }
    }

    //transform sums to means
    for (auto it = sums.begin(); it!= sums.end(); ++it) {
        sums[it->first] /= count[it->first];
    }

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    deviations[it->first] += std::pow(it->second - sums[it->first], 2);
                }
            }
        }
    }

    for (auto it = deviations.begin(); it!= deviations.end(); ++it) {
        deviations[it->first] = std::floor((std::sqrt(deviations[it->first] / count[it->first])) * 100.0 + 0.5) / 100.0;
    }

    return deviations;
}

static std::unordered_map<std::string, std::map<double,int>> atmoTable = {
        { "O3",{
                       {29, 1}, {54, 2}, {79, 3}, {104, 4}, {129, 5}, {149, 6}, {179, 7}, {209, 8}, {239, 9}
               }
        },
        { "SO2",{
                       {39, 1}, {79, 2}, {119, 3}, {159, 4}, {199, 5}, {249, 6}, {299, 7}, {399, 8}, {499, 9}
               }
        },
        { "NO2",{
                       {29, 1}, {54, 2}, {84, 3}, {109, 4}, {134, 5}, {164, 6}, {199, 7}, {274, 8}, {399, 9}
               }
        },
        { "PM10",{
                       {6, 1}, {13, 2}, {20, 3}, {27, 4}, {34, 5}, {41, 6}, {49, 7}, {64, 8}, {79, 9}
               }
        }
};

double Aggregation::computeAtmo() {
    //contract : we always get data representing one day

    double pm10 = 0.0;
    double so2 = 0.0;
    double no2 = 0.0;
    double o3 = 0.0;


    ///////// PM10 /////////
    /* moyenne de la journée */
    double pm_sum = 0.0;
    int pm_count = 0;

    for (auto i = points.begin(); i != points.end() ; ++i)
    {
        for (auto j = i->begin(); j != i->end() ; ++j)
        {
            for (auto k = j->begin(); k != j->end() ; ++k)
            {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it)
                {
                    if (it->first == "PM10") {
                        pm_sum += it->second;
                        pm_count++;
                    }
                }
            }
        }
    }
    pm10 = pm_sum / pm_count;
    ///////// END PM10 /////////

    /////// SO3 - O3 - NO2 ////////
    /* moyenne des maxima par heure */
    int iterPerHour = points.size() / 24;
    std::unordered_map<int, std::unordered_map<std::string, double>> maxima;
    std::unordered_map<std::string, double> means;
    int currentIter = 0;
    int currentHour = 0;
    for (auto i = points.begin(); i != points.end() ; ++i) {
        for (auto j = i->begin(); j != i->end() ; ++j) {
            for (auto k = j->begin(); k != j->end() ; ++k) {
                for (std::unordered_map<std::string, int>::const_iterator it = k->begin();
                     it != k->end(); ++it) {
                    //initial values
                    if (!maxima[currentHour].count(it->first))
                    {
                        maxima[currentHour][it->first] = it->second;
                    }
                    //max
                    if (it->second > maxima[currentHour][it->first]) {
                        maxima[currentHour][it->first] = it->second;
                    }
                }
            }
        }
        currentIter++;
        if (currentIter == iterPerHour) {
            currentIter = 0;
            currentHour++;
        }
    }
    //sum maximas by attribute
    for (auto i = maxima.begin(); i != maxima.end(); ++i) {
        for (auto j = i->second.begin(); j != i->second.end() ; ++j) {
            means[j->first] += j->second;
        }
    }
    //transform to means
    for (auto i = means.begin(); i != means.end(); ++i) {
        means[i->first] /= 24.0;
    }

    so2 = means["SO2"];
    no2 = means["NO2"];
    o3 = means["O3"];
    /////// END SO3 - O3 - NO2 ////////
    int ind_pm10 = 0;
    int ind_so2 = 0;
    int ind_no2 = 0;
    int ind_o3 = 0;

    for(auto it = atmoTable["O3"].begin(); it !=  atmoTable["O3"].end() && ind_o3==0; ++it)
    {
        if (o3 < it->first) {
            ind_o3 = it->second;
        }
    }

    for(auto it = atmoTable["SO2"].begin(); it !=  atmoTable["SO2"].end() && ind_so2==0; ++it)
    {
        if (so2 < it->first) {
            ind_so2 = it->second;
        }
    }

    for(auto it = atmoTable["NO2"].begin(); it !=  atmoTable["NO2"].end() && ind_no2==0; ++it)
    {
        if (no2 < it->first) {
            ind_no2 = it->second;
        }
    }

    for(auto it = atmoTable["PM10"].begin(); it !=  atmoTable["PM10"].end() && ind_pm10==0; ++it)
    {
        if (pm10 < it->first) {
            ind_pm10 = it->second;
        }
    }

    if (ind_pm10 == 0) {
        ind_pm10 = 10;
    }
    if (ind_so2 == 0) {
        ind_so2 = 10;
    }
    if (ind_o3 == 0) {
        ind_o3 = 10;
    }
    if (ind_no2 == 0) {
        ind_no2 = 10;
    }

    int indArr[] = { ind_no2, ind_o3, ind_so2, ind_pm10 };
    auto it = std::max_element(std::begin(indArr), std::end(indArr));

    return *it;
}

Aggregation &Aggregation::operator=(Aggregation other) {
    swap(*this, other);
    return *this;
}

Aggregation::Aggregation(const Aggregation &other) {
    points = other.points;
}

Aggregation::Aggregation(pointCollection & data) : points(data) {

}

Aggregation::~Aggregation() {

}

json* Aggregation::apply() {
    auto avg = computeAverage();
    auto extrems = computeExtrems();
    auto deviations = computeDeviation();

    json* j = new json;

    for (auto it = deviations.begin(); it!= deviations.end(); ++it) {
        (*j)[it->first]["avg"] = avg[it->first];
        (*j)[it->first]["min"] = extrems[it->first].first;
        (*j)[it->first]["max"] = extrems[it->first].second;
        (*j)[it->first]["deviation"] = deviations[it->first];
    }

    (*j)["atmo"] = computeAtmo();

    return j;
}

void swap(Aggregation &first, Aggregation &second) {
    std::swap(first.points, second.points);
}
